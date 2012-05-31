#pragma once
#include <cassert>

#if defined(_MSC_VER)
	#ifdef _DEBUG
		#include "nBase.hpp"
		#include <windows.h>

		namespace NLib
		{
			extern bool NAssertFunction(bool bResult, const char* szExpression, const char* szDescription, const char* szLine, const char* szFilename, const char* szFunction, bool* pbIgnoreAlways);
			extern bool NAssert_StdAssert;
		}

		#define NAssert(szExpression, szDescription) \
		{\
			static bool bIgnoreAlways = false;\
			if(!bIgnoreAlways) \
			{\
				if(NAssert_StdAssert)\
				{\
					assert(szExpression && szDescription); \
				}\
				else if(NLib::NAssertFunction(szExpression, NMAKE_STRING_A(szExpression), szDescription, NMAKE_STRING_A(__LINE__), __FILE__, __FUNCTION__, &bIgnoreAlways))\
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
		#define NAssert(expression, szDescription) (__assume(szExpression))
	#endif
#else
	#define NAssert(expression, szDescription) assert(expression && szDescription)
#endif