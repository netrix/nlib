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
   class SocketClient
   {
   public:
      SocketClient();
      ~SocketClient();

      bool	initClient(const char* szServerIPAddress, NUint16 uPort);
      void	initClient(SOCKET pSocket, sockaddr_in& adr);
      void	release();

      bool	sendRequest(const void* pData, NUint32 uDataSize);
      bool	getResponse(void* pBuffer, NUint32 uBufferSize);

      bool	isValid() const;

   public:
      const static NSize_t MAX_IP_ADDRESS_LENGTH = 30;

   private:
      char		   m_szServerIPAddress[MAX_IP_ADDRESS_LENGTH];
      NUint16	   m_uPort;
      bool		   m_bValid;
      SOCKET	   m_pClientSocket;
      sockaddr_in m_adrInfo;
   };
}	// Sockets
}	// NLib