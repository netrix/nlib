#pragma once
#include <new>

#ifndef _MSC_VER
	#include <stdlib.h>	// int posix_memalign(void **memptr, size_t alignment, size_t size);
#endif

namespace NLib
{
#ifdef _MSC_VER
	typedef __int8				NInt8;
	typedef __int16				NInt16;
	typedef __int32				NInt32;
	typedef __int64				NInt64;

	typedef unsigned __int8		NUint8;
	typedef unsigned __int16	NUint16;
	typedef unsigned __int32	NUint32;
	typedef unsigned __int64	NUint64;
#else
	typedef signed char			NInt8;
	typedef signed short		NInt16;
	typedef signed int			NInt32;
	typedef signed long long	NInt64;

	typedef unsigned char		NUint8;
	typedef unsigned short		NUint16;
	typedef unsigned int		NUint32;
	typedef unsigned long long	NUint64;
#endif

	#ifdef _WIN64
		typedef NUint64			NSize_t;
	#else
		typedef NUint32			NSize_t;
	#endif

	#ifdef _UNICODE
		typedef wchar_t			NChar;
	#else
		typedef char			NChar;
	#endif
}

#define NMAX_UINT32 0xffffffffu
#define NMAX_SIZE_T (NLib::NSize_t)-1

#define null 0
#define NNEW new (std::nothrow)
#define NUNUSED(value) value;

#ifdef _MSC_VER
	#define _NINLINE __forceinline
	#define _NALIGN_16 __declspec(align(16))
	#define NAlignedAlloc(ptr, size, alignment) *((void**)(ptr)) = _aligned_malloc((size), (alignment));	// void**, uint, uint
	#define NAlignedFree(ptr) _aligned_free(ptr);
#else
	#define _NINLINE inline
	#define _NALIGN_16 __attribute__((aligned (16)))
	#define NAlignedAlloc(ptr, size, alignment) posix_memalign((void**)(ptr), (alignment), (size));
	#define NAlignedFree(ptr) free(ptr);
#endif

#define NDELETE(ptr) {delete ptr;}
#define NDELETEARR(ptr) {delete[] ptr;}
#define NRELEASE(ptr) {ptr->Release();}
#define NDELETENULL(ptr) {delete ptr; ptr = null;}
#define NRELEASENULL(ptr) {ptr->Release(); ptr = null;}
#define NDELETEARRNULL(ptr) {delete[] ptr; ptr = null;}
#define NSAFERELEASE(ptr) if(ptr){ptr->Release();}
#define NSAFERELEASENULL(ptr) if(ptr){ptr->Release(); ptr = null;}

#define WIDEN(x) NTEXT(x)
#define NMS(exp) #exp

#define __WFILE__ WIDEN(__FILE__)
#define __WTIME__ WIDEN(__TIME__)
#define __WFUNCTION__ WIDEN(__FUNCTION__)
#define __WFUNCSIG__ WIDEN(__FUNCSIG__)

#define NMAKE_STRING_A(exp) NMS(exp)
#define NMAKE_STRING_W(exp) NTEXT(NMS(exp))

#ifdef _UNICODE
	#define NTEXT(string) L##string
	#define NMAKE_STRING(exp) NMAKE_STRING_W(exp)
#else
	#define NTEXT(string) string
	#define NMAKE_STRING(exp) NMAKE_STRING_A(exp)
#endif

// Endian Swap
#define	NEndianSwap16(type)  (((type >> 8) & 0x00ff) | ((type << 8) & 0xff00))
#define	NEndianSwap32(type)  (((type >> 24) & 0x000000ff) | ((type >> 8) & 0x0000ff00) | ((type << 8) & 0x00ff0000) | ((type <<24) & 0xff000000))

// Min/Max
#ifndef min
	#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
	#define max(a,b) ((a) > (b) ? (a) : (b))
#endif