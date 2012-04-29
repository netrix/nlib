#pragma once
#include "../Base/nBase.hpp"
#include <cwchar>

namespace NLib {
namespace Utilities
{
	_NINLINE char* NTrimToLocalPathA(char* szFullPath)
	{
		char* atSlash = strrchr(szFullPath, '/');
		char* atBackslash = strrchr(szFullPath, '\\');

		if(atSlash > atBackslash)		{ szFullPath = atSlash; }
		else if(atBackslash != null)	{ szFullPath = atBackslash;	}

		*szFullPath = null;
		return szFullPath;
	}

	_NINLINE wchar_t* NTrimToLocalPathW(wchar_t* szFullPath)
	{
		wchar_t* atSlash = wcsrchr(szFullPath, '/');
		wchar_t* atBackslash = wcsrchr(szFullPath, '\\');

		if(atSlash > atBackslash)		{ szFullPath = atSlash; }
		else if(atBackslash != null)	{ szFullPath = atBackslash;	}

		*szFullPath = null;
		return szFullPath;
	}

#ifdef _UNICODE
	#define NTrimToLocalPath NTrimToLocalPathW
#else
	#define NTrimToLocalPath NTrimToLocalPathA
#endif

	_NINLINE bool NStringAtBegin(const char* first, const char* second)
	{
		while(*first != 0 && *second != 0 && *first == *second)
		{
			++first;
			++second;
		}

		return *second == 0;
	}
}
}
