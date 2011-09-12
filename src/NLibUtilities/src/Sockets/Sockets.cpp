/*********************************************************************

Name:		Raytracer
Author:		Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/
#include "../../NLib/Sockets/Sockets.hpp"
#include <string.h>
#include <stdio.h>
#include "nLogger.hpp"

#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "ws2_32.lib")      // Niezbedna bibliotek
#else
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <sys/socket.h>
#endif

namespace NLib {
namespace Sockets
{
	////////////////////////////////////////////////////////////////////
	// SocketClient
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

	bool SocketClient::getResponse(void* pBuffer, NUint32 uBufferSize)
	{
		//int ret = recv(m_pClientSocket, (char*)pBuffer, uBufferSize, MSG_WAITALL | MSG_NOSIGNAL);
		//m_bValid = ret >= 0;
		//return !(ret > 0);

		NInt32 uResult = 0;
		do
		{
			uResult = recv(m_pClientSocket, (char*)pBuffer, uBufferSize, MSG_NOSIGNAL);

			if(uResult <= 0)	{ m_bValid = false; return true; }
			uBufferSize -= uResult;
			pBuffer = (char*)pBuffer + uResult;
		}
		while(uBufferSize > 0);

		return false;
	}

	////////////////////////////////////////////////////////////////////
	// SocketServer
	bool SocketServer::initServer(unsigned short uPort, NUint32 uMaxConn)
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

	void SocketServer::release()
	{
		closesocket(m_pClientSocket);
		m_bValid = false;
	}

	bool SocketServer::checkRequest()
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
		return !(m_bValid = m_pClientSocket > 0);
	}
}
}