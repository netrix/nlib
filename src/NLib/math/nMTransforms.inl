#pragma once
// Included in nMath.hpp

namespace NLib {
namespace Math
{
	/****************************************************/
	// Declarations
	_NINLINE NMVector NMVector3fTransformCoord(NMVectorPP vector, NMMatrixPP matrix);
	_NINLINE NMVector NMVector3fTransformNormal(NMVectorPP vector, NMMatrixPP matrix);
	_NINLINE NMVector NMVector3fDivByW(NMVectorPP vector);
	/****************************************************/
	// Definitions
	_NINLINE NMVector NMVector3fTransformCoord(NMVectorPP vector, NMMatrixPP matrix)
	{
		NMVector result;
	#ifdef _SSE_ENABLED
		result = _mm_mul_ps(matrix.r[0], NMShuffleXXXX(vector));
		result = _mm_add_ps(result, _mm_mul_ps(matrix.r[1], NMShuffleYYYY(vector)));
		result = _mm_add_ps(result, _mm_mul_ps(matrix.r[2], NMShuffleZZZZ(vector)));
		result = _mm_add_ps(result, matrix.r[3]);
		result = _mm_div_ps(result, NMShuffleWWWW(result));
	#else
		result = NMVectorMul(matrix.r[0], NMVectorLoad(vector.x));
		result += NMVectorMul(matrix.r[1], NMVectorLoad(vector.y));
		result += NMVectorMul(matrix.r[2], NMVectorLoad(vector.z));
		result += matrix.r[3];
		result /= result.w;
	#endif
		return result;
	}

	_NINLINE NMVector NMVector3fTransformNormal(NMVectorPP vector, NMMatrixPP matrix)
	{
		NMVector result;
	#ifdef _SSE_ENABLED
		result = _mm_mul_ps(matrix.r[0], NMShuffleXXXX(vector));
		result = _mm_add_ps(result, _mm_mul_ps(matrix.r[1], NMShuffleYYYY(vector)));
		result = _mm_add_ps(result, _mm_mul_ps(matrix.r[2], NMShuffleZZZZ(vector)));
	#else
		result = NMVectorMul(matrix.r[0], NMVectorLoad(vector.x));
		result += NMVectorMul(matrix.r[1], NMVectorLoad(vector.y));
		result += NMVectorMul(matrix.r[2], NMVectorLoad(vector.z));
	#endif
		return result;
	}

	_NINLINE NMVector NMVector3fDivByW(NMVectorPP vector)
	{
		NMVector result;
	#ifdef _SSE_ENABLED
		result = _mm_div_ps(vector, NMShuffleWWWW(vector));
	#else
		result = NMVectorDiv(vector, vector.w);
	#endif
		return result;
	}
}
}