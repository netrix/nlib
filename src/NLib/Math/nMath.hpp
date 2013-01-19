#pragma once
#include <NLib/Base/nBase.hpp>
#include <math.h>

#ifdef _SSE_ENABLED
	#include <xmmintrin.h>
	#define NSHUFFLE(va, vb, x, y, z, w) _mm_shuffle_ps(va, vb, (w << 6) | (z << 4) | (y << 2) | x)
#endif

#pragma warning(disable: 4201)	// Nonstandard extension for nameless structs

namespace NLib {
namespace Math
{
	/****************************************************/
	// NMVector
#ifdef _SSE_ENABLED
	typedef __m128 NMVector;	// Aligned to 16
#else
	typedef struct __NVec4f
	{
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float v[4];
		};
	} NMVector;
#endif

	// Parameter passing optimization
#ifdef _SSE_ENABLED
	typedef const NMVector NMVectorPP;
#else
	typedef const NMVector& NMVectorPP;
#endif

	/****************************************************/
	// NMMatrix
#ifdef _SSE_ENABLED
	typedef _NALIGN_16 struct __NMat4x4f
#else
	typedef struct __NMat4x4f
#endif
	{
		union
		{
			NMVector r[4];
			struct
			{
				float m11, m12, m13, m14,
					  m21, m22, m23, m24,
					  m31, m32, m33, m34,
					  m41, m42, m43, m44;
			};
			float m[4][4];
		};

		__NMat4x4f()
		{}

		__NMat4x4f(const __NMat4x4f& src)
		{
			r[0] = src.r[0];
			r[1] = src.r[1];
			r[2] = src.r[2];
			r[3] = src.r[3];
		}

		const __NMat4x4f& operator=(const __NMat4x4f& src)
		{
			r[0] = src.r[0];
			r[1] = src.r[1];
			r[2] = src.r[2];
			r[3] = src.r[3];
			return *this;
		}
	} NMMatrix;

	// Parameter passing optimization
	typedef const NMMatrix& NMMatrixPP;

	/****************************************************/

	struct NMVector4f
	{
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float v[4];
		};
	};

	struct NMVector3f
	{
		union
		{
			struct
			{
				float x, y, z;
			};
			float v[3];
		};
	};

	struct NMVector2f
	{
		union
		{
			struct
			{
				float x, y;
			};
			float v[2];
		};
	};

	struct NMMatrix4x4f
	{
		union
		{
			struct
			{
				float m11, m12, m13, m14,
					  m21, m22, m23, m24,
					  m31, m32, m33, m34,
					  m41, m42, m43, m44;
			};
			NMVector4f r[4];
			float m[4][4];
		};
	};

	struct NMMatrix3x4f
	{
		union
		{
			struct
			{
				float m11, m12, m13, m14,
					  m21, m22, m23, m24,
					  m31, m32, m33, m34;
			};
			NMVector4f r[3];
			float m[3][4];
		};
	};

	/****************************************************/
	// Additional functions
	_NINLINE void NMSinCos(float* pfSin, float* pfCos, float fAngle) // Radians
	{
	#ifdef _WIN64
		*pfSin = sin(fAngle);
		*pfCos = cos(fAngle);
	#elif _MSC_VER
		__asm
		{
			mov eax, pfSin;
			mov edx, pfCos;

			fld     fAngle;
			fsincos;
			fstp    dword ptr [edx];
			fstp    dword ptr [eax];
		}
	#else
		__asm__
		(
			"fld %2;"
			"fsincos;"
			"fstp %0;"
			"fstp %1;"
			: "=g" (*pfCos), "=g" (*pfSin)
			: "t" (fAngle)
			:
		);
	#endif
	}

	/****************************************************/
	// NMVector SSE constants
	typedef _NALIGN_16 struct __NVec4fv
	{
		union
		{
			float f[4];
			NMVector v;
		};
	} __NVec4fv;

	typedef _NALIGN_16 struct __NVec4iv
	{
		union
		{
			int i[4];
			NMVector v;
		};
	} __NVec4iv;

	typedef _NALIGN_16 struct __NVec4uv
	{
		union
		{
			unsigned int u[4];
			NMVector v;
		};
	} __NVec4uv;

#ifdef _MSC_VER
	#define NMGlobalConst extern const __declspec(selectany)
#else
	#define NMGlobalConst extern const __attribute__((weak))
#endif

	NMGlobalConst __NVec4fv NMCVector4fIdentityRow0	= { 1.0f, 0.0f, 0.0f, 0.0f };
	NMGlobalConst __NVec4fv NMCVector4fIdentityRow1	= { 0.0f, 1.0f, 0.0f, 0.0f };
	NMGlobalConst __NVec4fv NMCVector4fIdentityRow2	= { 0.0f, 0.0f, 1.0f, 0.0f };
	NMGlobalConst __NVec4fv NMCVector4fIdentityRow3	= { 0.0f, 0.0f, 0.0f, 1.0f };

	NMGlobalConst __NVec4fv NMCVector3fOne			= { 1.0f, 1.0f, 1.0f, 0.0f };
	NMGlobalConst __NVec4fv NMCVector4fNegOne3One	= { -1.0f, -1.0f, -1.0f, 1.0f };

	NMGlobalConst __NVec4uv NMCVector4fFull			= { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff };

#ifdef _SSE_ENABLED
	NMGlobalConst __NVec4iv NMCVector3fTruncMask	= { 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000 };

	#define NMVector3fTrunc(vec) _mm_and_ps(vec, NMCVector3fTruncMask.v)

	#define NMShuffleXXXX(vec) NSHUFFLE(vec, vec, 0, 0, 0, 0)
	#define NMShuffleYYYY(vec) NSHUFFLE(vec, vec, 1, 1, 1, 1)
	#define NMShuffleZZZZ(vec) NSHUFFLE(vec, vec, 2, 2, 2, 2)
	#define NMShuffleWWWW(vec) NSHUFFLE(vec, vec, 3, 3, 3, 3)
	#define NMShuffleXXXW(vec) NSHUFFLE(vec, vec, 0, 0, 0, 3)
	#define NMShuffleYYYW(vec) NSHUFFLE(vec, vec, 1, 1, 1, 3)
	#define NMShuffleZZZW(vec) NSHUFFLE(vec, vec, 2, 2, 2, 3)
	#define NMShuffleWZNN(vec) NSHUFFLE(vec, vec, 3, 2, 0, 0)	// n - nan or not important, just dont use
	#define NMShuffleZWNN(vec) NSHUFFLE(vec, vec, 2, 3, 0, 0)
	#define NMShuffleYNNN(vec) NSHUFFLE(vec, vec, 1, 0, 0, 0)
	#define NMShuffleZNNN(vec) NSHUFFLE(vec, vec, 2, 0, 0, 0)
	#define NMShuffleWNNN(vec) NSHUFFLE(vec, vec, 3, 0, 0, 0)
	#define NMShuffleYNNW(vec) NSHUFFLE(vec, vec, 1, 0, 0, 3)
	#define NMShuffleZNNW(vec) NSHUFFLE(vec, vec, 2, 0, 0, 3)
	#define NMShuffleWNNW(vec) NSHUFFLE(vec, vec, 3, 0, 0, 3)
	#define NMShuffleZWNW(vec) NSHUFFLE(vec, vec, 2, 3, 0, 3)
	#define NMShuffleYYXX(vec) NSHUFFLE(vec, vec, 1, 1, 0, 0)
	#define NMShuffleWWZZ(vec) NSHUFFLE(vec, vec, 3, 3, 2, 2)
	#define NMShuffleZYYX(vec) NSHUFFLE(vec, vec, 2, 1, 1, 0)
	#define NMShuffleWWZW(vec) NSHUFFLE(vec, vec, 3, 3, 2, 3)
	#define NMShuffleYXWZ(vec) NSHUFFLE(vec, vec, 1, 0, 3, 2)
	#define NMShuffleWZYX(vec) NSHUFFLE(vec, vec, 3, 2, 1, 0)
	#define NMShuffleYZXN(vec) NSHUFFLE(vec, vec, 1, 2, 0, 0)
	#define NMShuffleZXYN(vec) NSHUFFLE(vec, vec, 2, 0, 1, 0)
	#define NMShuffleZWXY(vec) NSHUFFLE(vec, vec, 2, 3, 0, 1)
#endif

	NMGlobalConst float NM_PI_F = 3.141592654f;
	NMGlobalConst float NM_1BYPI_F = 0.318309886f;
	NMGlobalConst float NM_EPSILON_F = 0.0000000596f;
	NMGlobalConst double NM_PI = 3.14159265358979323846264338327950;
	NMGlobalConst double NM_1BYPI = 0.31830988618379067153776752674503;
	NMGlobalConst double NM_EPSILON = 0.000000000000000111;
}
}

#define NM_IN_EPSILON_F(val) ((val) > -NLib::NM_EPSILON_F) && ((val) < NLib::NM_EPSILON_F)
#define NM_IN_EPSILON(val) ((val) > -NLib::NM_EPSILON) && ((val) < NLib::NM_EPSILON)

#include "nMVector.inl"
#include "nMVector2f.inl"
#include "nMVector3f.inl"
#include "nMVector4f.inl"
#include "nMMatrix.inl"
#include "nMTransforms.inl"
#include "nMUtilities.inl"
