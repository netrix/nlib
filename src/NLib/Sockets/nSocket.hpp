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
   class Socket
   {
   protected:
      Socket();

      virtual ~Socket();

   private:
      static void initSockets();
      static void releaseSockets();

      static NLib::NSize_t s_uSocketCounter;
   };
}	// Sockets
}	// NLib