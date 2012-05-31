#pragma once
#include <cassert>

#if defined(_MSC_VER)
	#ifdef _DEBUG
		#include "nBase.hpp"
		#include <windows.h>

		namespace NLib
		{
			extern bool NAssertFunction(bool bResult, const char* szExpression, const char* szDescription, const char* szLine, const char* szFilename, const char* szFunction, bool* pbIgnoreAlways);
			extern bool NAssert_StdAssert_val;
		}

		#define NAssert(szExpression, szDescription) \
		{\
			static bool bIgnoreAlways = false;\
			if(!bIgnoreAlways) \
			{\
				if(NLib::NAssert_StdAssert_val)\
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

		#define NAssert_StdAssert(val)	NLib::NAssert_StdAssert_val = val;
	#else
		#define NAssert(expression, szDescription) (__assume(szExpression))
		#define NAssert_StdAssert(val)
	#endif
#else
	#define NAssert(expression, szDescription) assert(expression && szDescription)
	#define NAssert_StdAssert(val)
#endif