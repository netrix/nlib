#pragma once

#ifdef _DEBUG
	#include "nBase.hpp"
	#include <windows.h>

	namespace NLib
	{
		extern bool NAssertFunction(bool bResult, const char* szExpression, const char* szDescription, const char* szLine, const char* szFilename, const char* szFunction, bool* pbIgnoreAlways);
	}

	#define NAssert(szExpression, szDescription) \
	{\
		static bool bIgnoreAlways = false;\
		if(!bIgnoreAlways) \
		{\
			if(NLib::NAssertFunction(szExpression, NMAKE_STRING_A(szExpression), szDescription, NMAKE_STRING_A(__LINE__), __FILE__, __FUNCTION__, &bIgnoreAlways))\
			{\
				if(::IsDebuggerPresent())\
				{\
					__debugbreak();\
				}\
				else\
				{\
					exit(1);\
				}\
			}\
		}\
	}

#else
	#ifdef _MSC_VER
		#define NAssert(szExpression, szDescription) (__assume(szExpression))
	#else
		#define NAssert(szExpression, szDescription)
	#endif
#endif