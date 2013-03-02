/*********************************************************************

Name:		NLib/Sockets
Author:	Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/

#include "nSocket.hpp"
#include <NLib/Base/nLogger.hpp>

namespace NLib {
namespace Sockets
{

NLib::NSize_t Socket::s_uSocketCounter = 0;

Socket::Socket()
{
   initSockets();
}

Socket::~Socket()
{
   releaseSockets();
}

void Socket::initSockets()
{
#ifdef _WIN32
   if(0 == s_uSocketCounter)
   {
	   WSADATA wsaData;
	   ZeroMemory(&wsaData, sizeof(wsaData));

	   if(FAILED(WSAStartup(MAKEWORD(2,2), &wsaData)))	// MAKEWORD(2,2) - Wersja WinSock
	   {
         NLogError("Failed on 'WSAStartup(MAKEWORD(2,2), &wsaData)'");
	   }
   }
#endif

   s_uSocketCounter++;
}

void Socket::releaseSockets()
{
   --s_uSocketCounter;

#ifdef _WIN32
   if(0 == s_uSocketCounter)
   {
	   WSACleanup();
   }
#endif
}

}	// Sockets
}	// NLib