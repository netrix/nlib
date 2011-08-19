#pragma once
#include "../nBase.hpp"

namespace NLib {
namespace Utilities
{
	_NINLINE char* NTrimToLocalPathA(char* szFullPath)
	{
		char* atSlash = strrchr(szFullPath, '/');
		char* atBackslash = strrchr(szFullPath, '\\');

		if(atSlash > atBackslash)
		{
			szFullPath = atSlash;
		}
		else if(atBackslash != null)
		{
			szFullPath = atBackslash;
		}

		*szFullPath = null;
		return szFullPath;
	}

	_NINLINE wchar_t* NTrimToLocalPathW(wchar_t* szFullPath)
	{
		wchar_t* atSlash = wcsrchr(szFullPath, '/');
		wchar_t* atBackslash = wcsrchr(szFullPath, '\\');

		if(atSlash > atBackslash)
		{
			szFullPath = atSlash;
		}
		else if(atBackslash != null)
		{
			szFullPath = atBackslash;
		}

		*szFullPath = null;
		return szFullPath;
	}

#ifdef _UNICODE
	#define NTrimToLocalPath NTrimToLocalPathW
#else
	#define NTrimToLocalPath NTrimToLocalPathA
#endif
}
}