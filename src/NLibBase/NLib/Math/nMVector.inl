#pragma once
// Included in nMath.hpp

namespace NLib {
namespace Math
{
	/****************************************************/
	// Declarations
	_NINLINE NMVector NMVectorLoadAligned(const float* pFloats);
	_NINLINE NMVector NMVectorLoadAligned(const NMVector2f& vec);
	_NINLINE NMVector NMVectorLoadAligned(const NMVector3f& vec);
	_NINLINE NMVector NMVectorLoadAligned(const NMVector4f& vec);
	_NINLINE NMVector NMVectorLoad(const float* pFloats);
	_NINLINE NMVector NMVectorLoad(float f);
	_NINLINE NMVector NMVectorLoad(float x, float y);
	_NINLINE NMVector NMVectorLoad(float x, float y, float z);
	_NINLINE NMVector NMVectorLoad(float x, float y, float z, float w);
	_NINLINE NMVector NMVectorLoad(const NMVector2f& vec);
	_NINLINE NMVector NMVectorLoad(const NMVector3f& vec);
	_NINLINE NMVector NMVectorLoad(const NMVector4f& vec);

	_NINLINE NMVector NMVectorLoadZeros();

	_NINLINE void NMVectorStoreAligned(float* pFloats, NMVectorPP vec);
	_NINLINE void NMVectorStoreAligned(NMVector4f& vec4, NMVectorPP vec);
	_NINLINE void NMVectorStore(float* pFloats, NMVectorPP vec);
	_NINLINE void NMVectorStore(NMVector2f& vec2, NMVectorPP vec);
	_NINLINE void NMVectorStore(NMVector3f& vec3, NMVectorPP vec);
	_NINLINE void NMVectorStore(NMVector4f& vec4, NMVectorPP vec);

	_NINLINE NMVector NMVectorAdd(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorSub(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorMul(NMVectorPP vecA, float f);
	_NINLINE NMVector NMVectorMul(float f, NMVectorPP vecA);
	_NINLINE NMVector NMVectorMul(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorDiv(NMVectorPP vecA, float f);
	_NINLINE NMVector NMVectorDiv(NMVectorPP vecA, NMVectorPP vecB);

	_NINLINE NMVector NMVectorMin(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorMax(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorAbs(NMVectorPP vec);
	_NINLINE NMVector NMVectorNeg(NMVectorPP vec);

	_NINLINE NMVector NMVectorAnd(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorAndNot(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorOr(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorNot(NMVectorPP vecv);

	_NINLINE NMVector NMVectorGreater(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVectorLess(NMVectorPP vecA, NMVectorPP vecB);

	_NINLINE NMVector operator+(NMVectorPP vec);
	_NINLINE NMVector operator-(NMVectorPP vec);
	_NINLINE NMVector operator+(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector operator-(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector operator*(NMVectorPP vecA, float f);
	_NINLINE NMVector operator*(float f, NMVectorPP vecA);
	_NINLINE NMVector operator*(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector operator/(NMVectorPP vecA, float f);
	_NINLINE NMVector operator/(NMVectorPP vecA, NMVectorPP vecB);

	_NINLINE NMVector& operator+=(NMVector& vecA, NMVectorPP vecB);
	_NINLINE NMVector& operator-=(NMVector& vecA, NMVectorPP vecB);
	_NINLINE NMVector& operator*=(NMVector& vecA, float f);
	_NINLINE NMVector& operator/=(NMVector& vecA, float f);

	_NINLINE NMVector operator&(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector operator|(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector operator~(NMVectorPP vec);

	_NINLINE NMVector operator>(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector operator<(NMVectorPP vecA, NMVectorPP vecB);

	_NINLINE float NMVector4fLength(NMVectorPP vec);
	_NINLINE float NMVector4fDot(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVector4fNormalize(NMVectorPP vec);

	_NINLINE float NMVector3fLength(NMVectorPP vec);
	_NINLINE float NMVector3fDot(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVector3fCross(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVector3fNormalize(NMVectorPP vec);
	_NINLINE NMVector NMVector3fReflect(NMVectorPP vec, NMVectorPP normal);
	_NINLINE NMVector NMVector3fReflectNormalized(NMVectorPP vec, NMVectorPP normal);

	_NINLINE float NMVector2fLength(NMVectorPP vec);
	_NINLINE float NMVector2fDot(NMVectorPP vecA, NMVectorPP vecB);
	_NINLINE NMVector NMVector2fNormalize(NMVectorPP vec);

	/****************************************************/
	// Definitions
	_NINLINE NMVector NMVectorLoadAligned(const float* pFloats)
	{
	#ifdef _SSE_ENABLED
		return _mm_load_ps(pFloats);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&pFloats[0]))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&pFloats[1]))[0];
		((NUint32*)&temp.z)[0] = ((const NUint32*)(&pFloats[2]))[0];
		((NUint32*)&temp.w)[0] = ((const NUint32*)(&pFloats[3]))[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoadAligned(const NMVector2f& vec)
	{
	#ifdef _SSE_ENABLED
		return _mm_load_ps((float*)&vec);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&vec.y))[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoadAligned(const NMVector3f& vec)
	{
	#ifdef _SSE_ENABLED
		return _mm_load_ps((float*)&vec);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&temp.z)[0] = ((const NUint32*)(&vec.z))[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoadAligned(const NMVector4f& vec)
	{
	#ifdef _SSE_ENABLED
		return _mm_load_ps((float*)&vec);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)&vec.x)[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)&vec.y)[0];
		((NUint32*)&temp.z)[0] = ((const NUint32*)&vec.z)[0];
		((NUint32*)&temp.w)[0] = ((const NUint32*)&vec.w)[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoad(const float* pFloats)
	{
	#ifdef _SSE_ENABLED
		return _mm_loadu_ps(pFloats);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&pFloats[0]))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&pFloats[1]))[0];
		((NUint32*)&temp.z)[0] = ((const NUint32*)(&pFloats[2]))[0];
		((NUint32*)&temp.w)[0] = ((const NUint32*)(&pFloats[3]))[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoad(float f)
	{
	#ifdef _SSE_ENABLED
		return _mm_set1_ps(f);
	#else
		NMVector temp;
		temp.x = f;
		temp.y = f;
		temp.z = f;
		temp.w = f;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoad(float x, float y)
	{
	#ifdef _SSE_ENABLED
		return _mm_set_ps(0.0f, 0.0f, y, x);
	#else
		NMVector temp;
		temp.x = x;
		temp.y = y;
		temp.z = 0.0f;
		temp.w = 0.0f;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoad(float x, float y, float z)
	{
	#ifdef _SSE_ENABLED
		return _mm_set_ps(0.0f, z, y, x);
	#else
		NMVector temp;
		temp.x = x;
		temp.y = y;
		temp.z = z;
		temp.w = 0.0f;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoad(float x, float y, float z, float w)
	{
	#ifdef _SSE_ENABLED
		return _mm_set_ps(w, z, y, x);
	#else
		NMVector temp;
		temp.x = x;
		temp.y = y;
		temp.z = z;
		temp.w = w;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoad(const NMVector2f& vec)
	{
	#ifdef _SSE_ENABLED
		return _mm_loadu_ps((float*)&vec);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&vec.y))[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoad(const NMVector3f& vec)
	{
	#ifdef _SSE_ENABLED
		return _mm_loadu_ps((float*)&vec);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&temp.z)[0] = ((const NUint32*)(&vec.z))[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoad(const NMVector4f& vec)
	{
	#ifdef _SSE_ENABLED
		return _mm_loadu_ps((float*)&vec);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)&vec.x)[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)&vec.y)[0];
		((NUint32*)&temp.z)[0] = ((const NUint32*)&vec.z)[0];
		((NUint32*)&temp.w)[0] = ((const NUint32*)&vec.w)[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLoadZeros()
	{
	#ifdef _SSE_ENABLED
		return _mm_setzero_ps();
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = 0;
		((NUint32*)&temp.y)[0] = 0;
		((NUint32*)&temp.z)[0] = 0;
		((NUint32*)&temp.w)[0] = 0;
		return temp;
	#endif
	}

	_NINLINE void NMVectorStoreAligned(float* pFloats, NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		_mm_store_ps(pFloats, vec);
	#else
		((NUint32*)&pFloats[0])[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&pFloats[1])[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&pFloats[2])[0] = ((const NUint32*)(&vec.z))[0];
		((NUint32*)&pFloats[3])[0] = ((const NUint32*)(&vec.w))[0];
	#endif
	}

	_NINLINE void NMVectorStoreAligned(NMVector4f& vec4, NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		_mm_store_ps((float*)&vec4, vec);
	#else
		((NUint32*)&vec4.x)[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&vec4.y)[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&vec4.z)[0] = ((const NUint32*)(&vec.z))[0];
		((NUint32*)&vec4.w)[0] = ((const NUint32*)(&vec.w))[0];
	#endif
	}

	_NINLINE void NMVectorStore(float* pFloats, NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		_mm_storeu_ps(pFloats, vec);
	#else
		((NUint32*)&pFloats[0])[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&pFloats[1])[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&pFloats[2])[0] = ((const NUint32*)(&vec.z))[0];
		((NUint32*)&pFloats[3])[0] = ((const NUint32*)(&vec.w))[0];
	#endif
	}

	_NINLINE void NMVectorStore(NMVector2f& vec2, NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		NMVector t1 = NMShuffleYYYY(vec);
		_mm_store_ss(&vec2.x, vec);
		_mm_store_ss(&vec2.y, t1);
	#else
		((NUint32*)&vec2.x)[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&vec2.y)[0] = ((const NUint32*)(&vec.y))[0];
	#endif
	}

	_NINLINE void NMVectorStore(NMVector3f& vec3, NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		NMVector t1 = NMShuffleYYYY(vec);
		NMVector t2 = NMShuffleZZZZ(vec);
		_mm_store_ss(&vec3.x, vec);
		_mm_store_ss(&vec3.y, t1);
		_mm_store_ss(&vec3.z, t2);
	#else
		((NUint32*)&vec3.x)[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&vec3.y)[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&vec3.z)[0] = ((const NUint32*)(&vec.z))[0];
	#endif
	}

	_NINLINE void NMVectorStore(NMVector4f& vec4, NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		_mm_storeu_ps((float*)&vec4, vec);
	#else
		((NUint32*)&vec4.x)[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&vec4.y)[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&vec4.z)[0] = ((const NUint32*)(&vec.z))[0];
		((NUint32*)&vec4.w)[0] = ((const NUint32*)(&vec.w))[0];
	#endif
	}

	_NINLINE NMVector NMVectorAdd(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_add_ps(vecA, vecB);
	#else
		NMVector temp;
		temp.x = vecA.x + vecB.x;
		temp.y = vecA.y + vecB.y;
		temp.z = vecA.z + vecB.z;
		temp.w = vecA.w + vecB.w;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorSub(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_sub_ps(vecA, vecB);
	#else
		NMVector temp;
		temp.x = vecA.x - vecB.x;
		temp.y = vecA.y - vecB.y;
		temp.z = vecA.z - vecB.z;
		temp.w = vecA.w - vecB.w;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorMul(NMVectorPP vecA, float f)
	{
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_set1_ps(f);
		return _mm_mul_ps(vecA, temp);
	#else
		NMVector temp;
		temp.x = vecA.x * f;
		temp.y = vecA.y * f;
		temp.z = vecA.z * f;
		temp.w = vecA.w * f;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorMul(float f, NMVectorPP vecA)
	{
		return NMVectorMul(vecA, f);
	}

	_NINLINE NMVector NMVectorMul(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_mul_ps(vecA, vecB);
	#else
		NMVector temp;
		temp.x = vecA.x * vecB.x;
		temp.y = vecA.y * vecB.y;
		temp.z = vecA.z * vecB.z;
		temp.w = vecA.w * vecB.w;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorDiv(NMVectorPP vecA, float f)
	{
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_set1_ps(f);
		return _mm_div_ps(vecA, temp);
	#else
		NMVector temp;
		temp.x = vecA.x / f;
		temp.y = vecA.y / f;
		temp.z = vecA.z / f;
		temp.w = vecA.w / f;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorDiv(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_div_ps(vecA, vecB);
	#else
		NMVector temp;
		temp.x = vecA.x / vecB.x;
		temp.y = vecA.y / vecB.y;
		temp.z = vecA.z / vecB.z;
		temp.w = vecA.w / vecB.w;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorMin(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_min_ps(vecA, vecB);
	#else
		NMVector temp;
		temp.x = min(vecA.x, vecB.x);
		temp.y = min(vecA.y, vecB.y);
		temp.z = min(vecA.z, vecB.z);
		temp.w = min(vecA.w, vecB.w);
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorMax(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_max_ps(vecA, vecB);
	#else
		NMVector temp;
		temp.x = max(vecA.x, vecB.x);
		temp.y = max(vecA.y, vecB.y);
		temp.z = max(vecA.z, vecB.z);
		temp.w = max(vecA.w, vecB.w);
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorAbs(NMVectorPP vec)
	{
		return NMVectorMax(vec, NMVectorNeg(vec));
	}

	_NINLINE NMVector NMVectorNeg(NMVectorPP vec)
	{
		return NMVectorSub(NMVectorLoadZeros(), vec);
	}

	_NINLINE NMVector NMVectorAnd(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_and_ps(vecA, vecB);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((NUint32*)&vecA.x)[0] & ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ((NUint32*)&vecA.y)[0] & ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ((NUint32*)&vecA.z)[0] & ((NUint32*)&vecB.z)[0];
		((NUint32*)&temp.w)[0] = ((NUint32*)&vecA.w)[0] & ((NUint32*)&vecB.w)[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorAndNot(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_andnot_ps(vecA, vecB);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ~((NUint32*)&vecA.x)[0] & ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ~((NUint32*)&vecA.y)[0] & ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ~((NUint32*)&vecA.z)[0] & ((NUint32*)&vecB.z)[0];
		((NUint32*)&temp.w)[0] = ~((NUint32*)&vecA.w)[0] & ((NUint32*)&vecB.w)[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorOr(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_or_ps(vecA, vecB);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ((NUint32*)&vecA.x)[0] | ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ((NUint32*)&vecA.y)[0] | ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ((NUint32*)&vecA.z)[0] | ((NUint32*)&vecB.z)[0];
		((NUint32*)&temp.w)[0] = ((NUint32*)&vecA.w)[0] | ((NUint32*)&vecB.w)[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorNot(NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		return _mm_andnot_ps(vec, NMCVector4fFull.v);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = ~((NUint32*)&vec.x)[0];
		((NUint32*)&temp.y)[0] = ~((NUint32*)&vec.y)[0];
		((NUint32*)&temp.z)[0] = ~((NUint32*)&vec.z)[0];
		((NUint32*)&temp.w)[0] = ~((NUint32*)&vec.w)[0];
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorGreater(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_cmpgt_ps(vecA, vecB);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = vecA.x > vecB.x ? 0xffffffff : 0x0;
		((NUint32*)&temp.y)[0] = vecA.y > vecB.y ? 0xffffffff : 0x0;
		((NUint32*)&temp.z)[0] = vecA.z > vecB.z ? 0xffffffff : 0x0;
		((NUint32*)&temp.w)[0] = vecA.w > vecB.w ? 0xffffffff : 0x0;
		return temp;
	#endif
	}

	_NINLINE NMVector NMVectorLess(NMVectorPP vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return _mm_cmplt_ps(vecA, vecB);
	#else
		NMVector temp;
		((NUint32*)&temp.x)[0] = vecA.x < vecB.x ? 0xffffffff : 0x0;
		((NUint32*)&temp.y)[0] = vecA.y < vecB.y ? 0xffffffff : 0x0;
		((NUint32*)&temp.z)[0] = vecA.z < vecB.z ? 0xffffffff : 0x0;
		((NUint32*)&temp.w)[0] = vecA.w < vecB.w ? 0xffffffff : 0x0;
		return temp;
	#endif
	}

	_NINLINE NMVector operator+(NMVectorPP vec)
	{
		return vec;
	}

	_NINLINE NMVector operator-(NMVectorPP vec)
	{
		return NMVectorNeg(vec);
	}

	_NINLINE NMVector operator+(NMVectorPP vecA, NMVectorPP vecB)
	{
		return NMVectorAdd(vecA, vecB);
	}

	_NINLINE NMVector operator-(NMVectorPP vecA, NMVectorPP vecB)
	{
		return NMVectorSub(vecA, vecB);
	}

	_NINLINE NMVector operator*(NMVectorPP vecA, float f)
	{
		return NMVectorMul(vecA, f);
	}

	_NINLINE NMVector operator*(float f, NMVectorPP vecA)
	{
		return NMVectorMul(vecA, f);
	}

	_NINLINE NMVector operator*(NMVectorPP vecA, NMVectorPP vecB)
	{
		return NMVectorMul(vecA, vecB);
	}

	_NINLINE NMVector operator/(NMVectorPP vecA, float f)
	{
		return NMVectorDiv(vecA, f);
	}

	_NINLINE NMVector operator/(NMVectorPP vecA, NMVectorPP vecB)
	{
		return NMVectorDiv(vecA, vecB);
	}

	_NINLINE NMVector operator&(NMVectorPP vecA, NMVectorPP vecB)
	{
		return NMVectorAnd(vecA, vecB);
	}

	_NINLINE NMVector operator|(NMVectorPP vecA, NMVectorPP vecB)
	{
		return NMVectorOr(vecA, vecB);
	}

	_NINLINE NMVector operator~(NMVectorPP vec)
	{
		return NMVectorNot(vec);
	}

	_NINLINE NMVector operator>(NMVectorPP vecA, NMVectorPP vecB)
	{
		return NMVectorGreater(vecA, vecB);
	}

	_NINLINE NMVector operator<(NMVectorPP vecA, NMVectorPP vecB)
	{
		return NMVectorLess(vecA, vecB);
	}

	_NINLINE NMVector& operator+=(NMVector& vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return (vecA = _mm_add_ps(vecA, vecB));
	#else
		vecA.x += vecB.x;
		vecA.y += vecB.y;
		vecA.z += vecB.z;
		vecA.w += vecB.w;
		return vecA;
	#endif
	}

	_NINLINE NMVector& operator-=(NMVector& vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return (vecA = _mm_sub_ps(vecA, vecB));
	#else
		vecA.x -= vecB.x;
		vecA.y -= vecB.y;
		vecA.z -= vecB.z;
		vecA.w -= vecB.w;
		return vecA;
	#endif
	}

	_NINLINE NMVector& operator*=(NMVector& vecA, float f)
	{
	#ifdef _SSE_ENABLED
		return (vecA = _mm_mul_ps(vecA, _mm_set1_ps(f)));
	#else
		vecA.x *= f;
		vecA.y *= f;
		vecA.z *= f;
		vecA.w *= f;
		return vecA;
	#endif
	}

	_NINLINE NMVector& operator*=(NMVector& vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return (vecA = _mm_mul_ps(vecA, vecB));
	#else
		vecA.x *= vecB.x;
		vecA.y *= vecB.y;
		vecA.z *= vecB.z;
		vecA.w *= vecB.w;
		return vecA;
	#endif
	}

	_NINLINE NMVector& operator/=(NMVector& vecA, float f)
	{
	#ifdef _SSE_ENABLED
		return (vecA = _mm_div_ps(vecA, _mm_set1_ps(f)));
	#else
		vecA.x /= f;
		vecA.y /= f;
		vecA.z /= f;
		vecA.w /= f;
		return vecA;
	#endif
	}

	_NINLINE NMVector& operator/=(NMVector& vecA, NMVectorPP vecB)
	{
	#ifdef _SSE_ENABLED
		return (vecA = _mm_div_ps(vecA, vecB));
	#else
		vecA.x /= vecB.x;
		vecA.y /= vecB.y;
		vecA.z /= vecB.z;
		vecA.w /= vecB.w;
		return vecA;
	#endif
	}

	_NINLINE float NMVector4fDot(NMVectorPP vecA, NMVectorPP vecB)
	{
		float f;
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_mul_ps(vecA, vecB);
		temp = _mm_add_ps(temp, NMShuffleWZNN(temp));	// [ n n y+z x+w ]
		temp = _mm_add_ss(temp, NMShuffleYNNN(temp));   // [ n n n x+y+z+w ]
		_mm_store_ss(&f, temp);
	#else
		f = vecA.x * vecB.x;
		f += vecA.y * vecB.y;
		f += vecA.z * vecB.z;
		f += vecA.w * vecB.w;
	#endif
		return f;
	}

	_NINLINE float NMVector4fLength(NMVectorPP vec)
	{
		float f;
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_mul_ps(vec, vec);
		temp = _mm_add_ps(temp, NMShuffleWZNN(temp));	// [ n n y+w x+z ]
		temp = _mm_add_ss(temp, NMShuffleYNNN(temp));   // [ n n n x+y+z+w ]
		temp = _mm_sqrt_ss(temp);
		_mm_store_ss(&f, temp);
	#else
		f = NMVector4fDot(vec, vec);
		f = sqrtf(f);
	#endif
		return f;
	}

	_NINLINE NMVector NMVector4fNormalize(NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_mul_ps(vec, vec);
		temp = _mm_add_ps(temp, NMShuffleYXWZ(temp));	// [ w+z z+w y+x x+y ]
		temp = _mm_add_ps(temp, NMShuffleWZYX(temp));	// [ w+z+x+y z+w+y+x y+x+z+w x+y+z+w ]
		return _mm_div_ps(vec, _mm_sqrt_ps(temp));
	#else
		float f = NMVector4fLength(vec);
		return vec / f;
	#endif
	}

	_NINLINE float NMVector3fDot(NMVectorPP vecA, NMVectorPP vecB)
	{
		float f;
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_mul_ps(vecA, vecB);
		temp = _mm_add_ss(temp, NMShuffleZNNN(temp));
		temp = _mm_add_ss(temp, NMShuffleYNNN(temp));
		_mm_store_ss(&f, temp);
	#else
		f = vecA.x * vecB.x;
		f += vecA.y * vecB.y;
		f += vecA.z * vecB.z;
	#endif
		return f;
	}

	_NINLINE NMVector NMVector3fCross(NMVectorPP vecA, NMVectorPP vecB)
	{
		NMVector temp;
	#ifdef _SSE_ENABLED
		// Left side
		NMVector vTemp1 = NMShuffleYZXN(vecA);
		NMVector vTemp2 = NMShuffleZXYN(vecB);
		temp = _mm_mul_ps(vTemp1, vTemp2);
		// Right side
		vTemp1 = NMShuffleYZXN(vTemp1);
		vTemp2 = NMShuffleZXYN(vTemp2);
		vTemp1 = _mm_mul_ps(vTemp1, vTemp2);
		temp = NMVector3fTrunc(_mm_sub_ps(temp, vTemp1));
	#else
		temp.x = vecA.y * vecB.z - vecA.z * vecB.y;
		temp.y = vecA.z * vecB.x - vecA.x * vecB.z;
		temp.z = vecA.x * vecB.y - vecA.y * vecB.x;
		temp.w = 0.0f;
	#endif
		return temp;
	}

	_NINLINE float NMVector3fLength(NMVectorPP vec)
	{
		float f;
	#ifdef _SSE_ENABLED
		NMVector temp = NMVector3fTrunc((_mm_mul_ps(vec, vec)));
		temp = _mm_add_ps(temp, NMShuffleZWNN(temp));
		temp = _mm_add_ss(temp, NMShuffleYNNN(temp));
		temp = _mm_sqrt_ss(temp);
		_mm_store_ss(&f, temp);
	#else
		f = sqrt(NMVector3fDot(vec, vec));
	#endif
		return f;
	}

	_NINLINE NMVector NMVector3fNormalize(NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		NMVector temp = NMVector3fTrunc((_mm_mul_ps(vec, vec)));
		temp = _mm_add_ps(temp, NMShuffleYXWZ(temp));
		temp = _mm_add_ps(temp, NMShuffleWZYX(temp));
		return _mm_div_ps(vec, _mm_sqrt_ps(temp));
	#else
		float f = NMVector3fLength(vec);
		return vec / f;
	#endif
	}

	_NINLINE NMVector NMVector3fReflect(NMVectorPP vec, NMVectorPP normal)
	{
		return vec - NMVectorMul(normal, 2 * NMVector3fDot(vec, normal));
	}

	_NINLINE NMVector NMVector3fReflectNormalized(NMVectorPP vec, NMVectorPP normal)
	{
		return vec - NMVectorMul(normal, 2 * NMVector3fDot(vec, normal) / NMVector3fDot(normal, normal));
	}

	_NINLINE float NMVector2fDot(NMVectorPP vecA, NMVectorPP vecB)
	{
		float f;
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_mul_ps(vecA, vecB);
		temp = _mm_add_ss(temp, NMShuffleYNNN(temp));
		_mm_store_ss(&f, temp);
	#else
		f = vecA.x * vecB.x;
		f += vecA.y * vecB.y;
	#endif
		return f;
	}

	_NINLINE float NMVector2fLength(NMVectorPP vec)
	{
		float f;
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_mul_ps(vec, vec);
		temp = _mm_add_ss(temp, NMShuffleYNNN(temp));
		temp = _mm_sqrt_ss(temp);
		_mm_store_ss(&f, temp);
	#else
		f = NMVector2fDot(vec, vec);
		f = sqrt(f);
	#endif
		return f;
	}

	_NINLINE NMVector NMVector2fNormalize(NMVectorPP vec)
	{
	#ifdef _SSE_ENABLED
		NMVector temp = _mm_mul_ps(vec, vec);
		temp = _mm_add_ps(temp, NMShuffleYNNN(temp));
		return _mm_div_ps(vec, _mm_sqrt_ps(temp));
	#else
		float f = NMVector2fLength(vec);
		return vec / f;
	#endif
	}
}
}