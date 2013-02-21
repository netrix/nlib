/*********************************************************************

Name:		NLib/Sockets
Author:	Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/
#pragma once

#include "nCommon.hpp"

namespace NLib {
namespace Sockets
{
   class SocketServer
   {
   public:
      SocketServer();
      ~SocketServer();

      bool initServer(unsigned short uPort, NUint32 uMaxConn);

      void release();

      bool checkRequest();

      bool sendResponse(const void* pData, NUint32 uDataSize);

      void shutRequest();

      bool isValid() const;

      SOCKET getClientSocket();

      void getClientAddr(sockaddr_in* pAddr);

      NUint32 getMaxConnections() const;

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
}	// Sockets
}	// NLib