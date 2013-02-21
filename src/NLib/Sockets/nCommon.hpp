/*********************************************************************

Name:		NLib/Sockets
Author:		Kamil Szatkowski "Netrix" (C)
Website:	http://www.netrix.org.pl/
License:	GNU GPL

*********************************************************************/
#pragma once

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif

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