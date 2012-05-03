/*********************************************************************

Name:		Raytracer
Author:		Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifdef _WIN32
	#include <winsock2.h>
	#define MSG_NOSIGNAL 0
#else
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <unistd.h>
	typedef int SOCKET;
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
	#define closesocket close
#endif

#include <NLib/Base/nBase.hpp>
#define BUFFER_SIZE 2048

#pragma warning(disable: 4996)

namespace NLib {
namespace Sockets
{
	class SocketClient
	{
	public:
		SocketClient()															: m_bValid(false) {}
		~SocketClient()															{ release(); }

		bool	initClient(const char* szServerIPAddress, NUint16 uPort);
		void	initClient(SOCKET pSocket, sockaddr_in& adr);
		void	release();

		bool	sendRequest(const void* pData, NUint32 uDataSize)			{ return !(m_bValid = send(m_pClientSocket, (const char*)pData, uDataSize, MSG_NOSIGNAL) != SOCKET_ERROR); }
		bool	getResponse(void* pBuffer, NUint32 uBufferSize);

		bool	isValid() const													{ return m_bValid; }

	private:
		char		m_szServerIPAddress[30];
		NUint16		m_uPort;
		bool		m_bValid;
		SOCKET		m_pClientSocket;
		sockaddr_in m_adrInfo;
	};

	class SocketServer
	{
	public:
		SocketServer() : m_bValid(false) {}
		~SocketServer() { release(); }

		bool initServer(unsigned short uPort, NUint32 uMaxConn);

		void release();

		bool checkRequest();

		bool sendResponse(const void* pData, NUint32 uDataSize)
		{
			return send(m_pClientSocket, (const char*)pData, uDataSize, 0) == SOCKET_ERROR;
		}

		void shutRequest()
		{
			closesocket(m_pClientSocket);
		}

		bool isValid() const { return m_bValid; }

		SOCKET getClientSocket()				{ return m_pClientSocket; }
		void getClientAddr(sockaddr_in* pAddr)	{ *pAddr = m_adrClient; }
		NUint32 getMaxConnections() const			{ return m_uMaxConn; }

	private:
		NUint32 m_uMaxConn;
		NUint16 m_uPort;
		bool m_bValid;
		SOCKET m_pServerSocket;
		sockaddr_in m_adrInfo;

		// Request info
		sockaddr_in m_adrClient;
		#ifdef _WIN32
			int m_adrClientSize;
		#else
			socklen_t m_adrClientSize;
		#endif
		SOCKET m_pClientSocket;
	};
}
}
