/*********************************************************************

Name:		NLib/Sockets
Author:	Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/

#include "nClientSocket.hpp"
//#include <string.h>
#include <stdio.h>
#include <NLib/Base/nLogger.hpp>

#ifdef _WIN32
   #include <ws2tcpip.h>
   #pragma comment(lib, "ws2_32.lib")      // Niezbedna bibliotek
#else
   #include <arpa/inet.h>
   #include <netdb.h>
   #include <sys/socket.h>
#endif

#pragma warning(disable: 4996)

namespace NLib {
namespace Sockets
{

SocketClient::SocketClient()
   : m_bValid(false) 
{
}

SocketClient::~SocketClient()
{
   release(); 
}

bool SocketClient::initClient(const char* szServerIPAddress, NUint16 uPort)
{
   // Getting address from DNS
   char szPort[8];
   addrinfo hint	 = { 0 },
         * pResult = null;
   hint.ai_family = AF_INET;
   hint.ai_socktype = SOCK_STREAM;

   sprintf(szPort, "%u", uPort);
   if(getaddrinfo(szServerIPAddress, szPort, &hint, &pResult))
   {
   #ifdef _WIN32
      NLogFunctionError("getaddrinfo()", WSAGetLastError());
   #else
      NLogError("getaddrinfo() failed!\n");
   #endif
      closesocket(m_pClientSocket);
      return true;
   }

   // Empty address list
   if(pResult == null)
   {
      NLogError("Empty address list");
      return true;
   }

   // Connectiong
   //m_pClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   m_pClientSocket = socket(pResult->ai_family, pResult->ai_socktype, pResult->ai_protocol);
   if(m_pClientSocket == INVALID_SOCKET)
   {
   #ifdef _WIN32
      NLogFunctionError("socket()", WSAGetLastError());
   #else
      NLogError("socket() failed!\n");
   #endif
      return true;
   }

//	m_adrInfo.sin_family = AF_INET;
//	m_adrInfo.sin_port = htons(uPort);
//
//#ifdef _WIN32
//	m_adrInfo.sin_addr.S_un.S_addr = inet_addr(szServerIPAddress);
//#else
//	m_adrInfo.sin_addr.s_addr = inet_addr(szServerIPAddress);
//#endif

   //if(connect(m_pClientSocket, (sockaddr*)&m_adrInfo, sizeof(m_adrInfo)) == SOCKET_ERROR)
   if(connect(m_pClientSocket, pResult->ai_addr, (int)pResult->ai_addrlen))
   {
   #ifdef _WIN32
      NLogFunctionError("connect()", WSAGetLastError());
   #else
      NLogError("connect() failed\n");
   #endif
      closesocket(m_pClientSocket);
      return true;
   }

   // Releaseing addrinfo linked list
   freeaddrinfo(pResult);

   strcpy(m_szServerIPAddress, szServerIPAddress);
   m_uPort = uPort;
   m_bValid = true;

   return false;
}

void SocketClient::initClient(SOCKET pSocket, sockaddr_in& adr)
{
   m_pClientSocket = pSocket;
   m_adrInfo = adr;
   m_bValid = true;
}

void SocketClient::release()
{
   closesocket(m_pClientSocket);
   m_bValid = false;
}

bool SocketClient::sendRequest(const void* pData, NUint32 uDataSize)
{
   m_bValid = send(m_pClientSocket, (const char*)pData, uDataSize, MSG_NOSIGNAL) != SOCKET_ERROR;

   return m_bValid;
}

bool SocketClient::getResponse(void* pBuffer, NUint32 uBufferSize)
{
   //int ret = recv(m_pClientSocket, (char*)pBuffer, uBufferSize, MSG_WAITALL | MSG_NOSIGNAL);
   //m_bValid = ret >= 0;
   //return !(ret > 0);

   NInt32 uResult = 0;
   do
   {
      uResult = recv(m_pClientSocket, (char*)pBuffer, uBufferSize, MSG_NOSIGNAL);

      if(uResult <= 0)	
      { 
         m_bValid = false; 
         return true; 
      }
      uBufferSize -= uResult;
      pBuffer = (char*)pBuffer + uResult;
   }
   while(uBufferSize > 0);

   return false;
}

bool SocketClient::isValid() const
{ 
   return m_bValid; 
}

}	// Sockets
}	// NLib