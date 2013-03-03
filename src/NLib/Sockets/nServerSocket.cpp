/*********************************************************************

Name:		NLib/Sockets
Author:	Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/

#include "nServerSocket.hpp"
//#include <string.h>
//#include <stdio.h>
#include <NLib/Base/nLogger.hpp>

#ifdef _WIN32
   //#include <ws2tcpip.h>
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

ServerSocket::ServerSocket() 
   : m_bValid(false) 
{
}

ServerSocket::~ServerSocket() 
{ 
   release(); 
}

bool ServerSocket::initServer(NUint16 uPort, NUint32 uMaxConn)
{
   m_pServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(m_pServerSocket == INVALID_SOCKET)
   {
   #ifdef _WIN32
      NLogFunctionError("socket()", WSAGetLastError());
   #else
      NLogError("socket() failed!\n");
   #endif
      return true;
   }

   m_adrInfo.sin_family = AF_INET;
   m_adrInfo.sin_port = htons(uPort);

   #ifdef _WIN32
      m_adrInfo.sin_addr.S_un.S_addr = INADDR_ANY;
   #else
      m_adrInfo.sin_addr.s_addr = INADDR_ANY;
   #endif

   if(bind(m_pServerSocket, (sockaddr*)&m_adrInfo, sizeof(m_adrInfo)) == SOCKET_ERROR)
   {
   #ifdef _WIN32
      NLogFunctionError("bind()", WSAGetLastError());
   #else
      NLogError("bind() failed!\n");
   #endif
      closesocket(m_pClientSocket);
      return true;
   }

   if(listen(m_pServerSocket, uMaxConn) == SOCKET_ERROR)
   {
   #ifdef _WIN32
      NLogFunctionError("listen()", WSAGetLastError());
   #else
      NLogError("listen() failed!\n");
   #endif
      closesocket(m_pClientSocket);
      return true;
   }

   m_uMaxConn = uMaxConn;
   m_uPort = uPort;
   m_bValid = true;

   return false;
}

void ServerSocket::release()
{
	closesocket(m_pClientSocket);
	m_bValid = false;
}

bool ServerSocket::checkRequest()
{
	m_adrClientSize = sizeof(m_adrClient);
	timeval t = { 2 };
	fd_set sockSet;

	FD_ZERO(&sockSet);
	FD_SET(m_pServerSocket, &sockSet);

	m_pClientSocket = 0;
	if(select(FD_SETSIZE, &sockSet, 0, 0, &t) > 0)
	{
		m_pClientSocket = accept(m_pServerSocket, (sockaddr*)&m_adrClient, &m_adrClientSize);
	}

   m_bValid = m_pClientSocket > 0;

   return m_bValid;
}

bool ServerSocket::sendResponse(const void* pData, NUint32 uDataSize)
{
   return send(m_pClientSocket, (const char*)pData, uDataSize, 0) == SOCKET_ERROR;
}

void ServerSocket::shutRequest()
{
   closesocket(m_pClientSocket);
}

bool ServerSocket::isValid() const 
{ 
   return m_bValid; 
}

SOCKET ServerSocket::getClientSocket()
{ 
   return m_pClientSocket;
}

void ServerSocket::getClientAddr(sockaddr_in* pAddr)	
{ 
   *pAddr = m_adrClient; 
}

NUint32 ServerSocket::getMaxConnections() const
{ 
   return m_uMaxConn; 
}

}	// Sockets
}	// NLib