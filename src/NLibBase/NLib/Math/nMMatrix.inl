#pragma once
// Included in nMath.hpp

namespace NLib {
namespace Math
{
	/****************************************************/
	// Declarations
	_NINLINE NMMatrix NMMatrixLoadAligned(const float* pFloats);
	_NINLINE NMMatrix NMMatrixLoadAligned(const NMMatrix3x4f& mat);
	_NINLINE NMMatrix NMMatrixLoadAligned(const NMMatrix4x4f& mat);
	_NINLINE NMMatrix NMMatrixLoad(const float* pFloats);
	_NINLINE NMMatrix NMMatrixLoad(float m11, float m12, float m13, float m14,
								  float m21, float m22, float m23, float m24,
								  float m31, float m32, float m33, float m34,
								  float m41, float m42, float m43, float m44);
	_NINLINE NMMatrix NMMatrixLoad(NMVectorPP rowA, NMVectorPP rowB, NMVectorPP rowC, const NMVector& rowD);	// Pierwsze 3 parametry s¹ przekazywane przez rejestr, czwarty ju¿ nie
	_NINLINE NMMatrix NMMatrixLoad(const NMMatrix3x4f& mat);
	_NINLINE NMMatrix NMMatrixLoad(const NMMatrix4x4f& mat);

	_NINLINE void NMMatrixStoreAligned(float* pFloats, NMMatrixPP mat);
	_NINLINE void NMMatrixStoreAligned(NMMatrix3x4f& mat3x4, NMMatrixPP mat);
	_NINLINE void NMMatrixStoreAligned(NMMatrix4x4f& mat4x4, NMMatrixPP mat);
	_NINLINE void NMMatrixStore(float* pFloats, NMMatrixPP mat);
	_NINLINE void NMMatrixStore(NMMatrix3x4f& mat3x4, NMMatrixPP mat);
	_NINLINE void NMMatrixStore(NMMatrix4x4f& mat4x4, NMMatrixPP mat);

	_NINLINE NMMatrix NMMatrixLoadIdentity();
	_NINLINE NMMatrix NMMatrixLoadOrthoLH(float fW, float fH, float fZNear, float fZFar);
	_NINLINE NMMatrix NMMatrixLoadPerspectiveFovLH(float fFOVY, float fAspect, float fZNear, float fZFar);
	_NINLINE NMMatrix NMMatrixLoadLookAtLH(NMVectorPP eye, NMVectorPP at, NMVectorPP up);
	_NINLINE NMMatrix NMMatrixLoadScale(float x, float y, float z);
	_NINLINE NMMatrix NMMatrixLoadTranslation(float x, float y, float z);
	_NINLINE NMMatrix NMMatrixLoadTranslation(const NMVector3f& vector);
	_NINLINE NMMatrix NMMatrixLoadTranslation(NMVectorPP vector);
	_NINLINE NMMatrix NMMatrixLoadRotationNormalizedAxis(NMVectorPP vNormalizedAxis, float fAngle);
	_NINLINE NMMatrix NMMatrixLoadRotationAxis(NMVectorPP vAxis, float fAngle);

	_NINLINE NMMatrix NMMatrixAdd(NMMatrixPP matA, NMMatrixPP matB);
	_NINLINE NMMatrix NMMatrixSub(NMMatrixPP matA, NMMatrixPP matB);
	_NINLINE NMMatrix NMMatrixMul(NMMatrixPP matA, float f);
	_NINLINE NMMatrix NMMatrixMulEach(NMMatrixPP matA, NMMatrixPP matB);
	_NINLINE NMMatrix NMMatrixDiv(NMMatrixPP matA, float f);
	_NINLINE NMMatrix NMMatrixDivEach(NMMatrixPP matA, NMMatrixPP matB);

	_NINLINE NMMatrix operator+(NMMatrixPP matA, NMMatrixPP matB);
	_NINLINE NMMatrix operator-(NMMatrixPP matA, NMMatrixPP matB);
	_NINLINE NMMatrix operator*(NMMatrixPP matA, float f);
	_NINLINE NMMatrix operator*(float f, NMMatrixPP matA);
	_NINLINE NMMatrix operator*(NMMatrixPP matA, NMMatrixPP matB);
	_NINLINE NMMatrix operator/(NMMatrixPP matA, float f);
	_NINLINE NMMatrix operator/(NMMatrixPP matA, NMMatrixPP matB);

	_NINLINE NMMatrix& operator+=(NMMatrix& matA, NMMatrixPP matB);
	_NINLINE NMMatrix& operator-=(NMMatrix& matA, NMMatrixPP matB);
	_NINLINE NMMatrix& operator*=(NMMatrix& matA, float f);
	_NINLINE NMMatrix& operator/=(NMMatrix& matA, float f);

	_NINLINE NMMatrix NMMatrixMul(NMMatrixPP matA, NMMatrixPP matB);
	_NINLINE NMMatrix NMMatrixTranspose(NMMatrixPP mat);
	_NINLINE float NMMatrixDeterminant(NMMatrixPP mat);
	_NINLINE NMMatrix NMMatrixInverse(NMMatrixPP mat, float* ofDeterminant);

	/****************************************************/
	// Definitions
	_NINLINE NMMatrix NMMatrixLoadAligned(const float* pFloats)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorLoadAligned(pFloats);
		temp.r[1] = NMVectorLoadAligned(pFloats + 4);
		temp.r[2] = NMVectorLoadAligned(pFloats + 8);
		temp.r[3] = NMVectorLoadAligned(pFloats + 12);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadAligned(const NMMatrix3x4f& mat)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorLoadAligned(mat.m[0]);
		temp.r[1] = NMVectorLoadAligned(mat.m[1]);
		temp.r[2] = NMVectorLoadAligned(mat.m[2]);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadAligned(const NMMatrix4x4f& mat)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorLoadAligned(mat.m[0]);
		temp.r[1] = NMVectorLoadAligned(mat.m[1]);
		temp.r[2] = NMVectorLoadAligned(mat.m[2]);
		temp.r[3] = NMVectorLoadAligned(mat.m[3]);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoad(const float* pFloats)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorLoad(pFloats);
		temp.r[1] = NMVectorLoad(pFloats + 4);
		temp.r[2] = NMVectorLoad(pFloats + 8);
		temp.r[3] = NMVectorLoad(pFloats + 12);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoad(float m11, float m12, float m13, float m14,
								  float m21, float m22, float m23, float m24,
								  float m31, float m32, float m33, float m34,
								  float m41, float m42, float m43, float m44)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorLoad(m11, m12, m13, m14);
		temp.r[1] = NMVectorLoad(m21, m22, m23, m24);
		temp.r[2] = NMVectorLoad(m31, m32, m33, m34);
		temp.r[3] = NMVectorLoad(m41, m42, m43, m44);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoad(NMVectorPP rowA, NMVectorPP rowB, NMVectorPP rowC, const NMVector& rowD)
	{
		NMMatrix temp;
		temp.r[0] = rowA;
		temp.r[1] = rowB;
		temp.r[2] = rowC;
		temp.r[3] = rowD;
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoad(const NMMatrix3x4f& mat)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorLoad(mat.m[0]);
		temp.r[1] = NMVectorLoad(mat.m[1]);
		temp.r[2] = NMVectorLoad(mat.m[2]);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoad(const NMMatrix4x4f& mat)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorLoad(mat.m[0]);
		temp.r[1] = NMVectorLoad(mat.m[1]);
		temp.r[2] = NMVectorLoad(mat.m[2]);
		temp.r[3] = NMVectorLoad(mat.m[3]);
		return temp;
	}

	_NINLINE void NMMatrixStoreAligned(float* pFloats, NMMatrixPP mat)
	{
		NMVectorStoreAligned(pFloats, mat.r[0]);
		NMVectorStoreAligned(pFloats + 4, mat.r[1]);
		NMVectorStoreAligned(pFloats + 8, mat.r[2]);
		NMVectorStoreAligned(pFloats + 12, mat.r[3]);
	}

	_NINLINE void NMMatrixStoreAligned(NMMatrix3x4f& mat3x4, NMMatrixPP mat)
	{
		NMVectorStoreAligned(mat3x4.r[0], mat.r[0]);
		NMVectorStoreAligned(mat3x4.r[1], mat.r[1]);
		NMVectorStoreAligned(mat3x4.r[2], mat.r[2]);
	}

	_NINLINE void NMMatrixStoreAligned(NMMatrix4x4f& mat4x4, NMMatrixPP mat)
	{
		NMVectorStoreAligned(mat4x4.r[0], mat.r[0]);
		NMVectorStoreAligned(mat4x4.r[1], mat.r[1]);
		NMVectorStoreAligned(mat4x4.r[2], mat.r[2]);
		NMVectorStoreAligned(mat4x4.r[3], mat.r[3]);
	}

	_NINLINE void NMMatrixStore(float* pFloats, NMMatrixPP mat)
	{
		NMVectorStore(pFloats, mat.r[0]);
		NMVectorStore(pFloats + 4, mat.r[1]);
		NMVectorStore(pFloats + 8, mat.r[2]);
		NMVectorStore(pFloats + 12, mat.r[3]);
	}

	_NINLINE void NMMatrixStore(NMMatrix3x4f& mat3x4, NMMatrixPP mat)
	{
		NMVectorStore(mat3x4.r[0], mat.r[0]);
		NMVectorStore(mat3x4.r[1], mat.r[1]);
		NMVectorStore(mat3x4.r[2], mat.r[2]);
	}

	_NINLINE void NMMatrixStore(NMMatrix4x4f& mat4x4, NMMatrixPP mat)
	{
		NMVectorStore(mat4x4.r[0], mat.r[0]);
		NMVectorStore(mat4x4.r[1], mat.r[1]);
		NMVectorStore(mat4x4.r[2], mat.r[2]);
		NMVectorStore(mat4x4.r[3], mat.r[3]);
	}

	_NINLINE NMMatrix NMMatrixLoadIdentity()
	{
		NMMatrix temp;
		temp.r[0] = NMCVector4fIdentityRow0.v;
		temp.r[1] = NMCVector4fIdentityRow1.v;
		temp.r[2] = NMCVector4fIdentityRow2.v;
		temp.r[3] = NMCVector4fIdentityRow3.v;
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadOrthoLH(float fW, float fH, float fZNear, float fZFar)
	{
		NMMatrix temp;
		float fZTemp = 1.0f / (fZFar - fZNear);
		temp.r[0] = NMVectorLoad(2.0f / fW, 0.0f, 0.0f, 0.0f);
		temp.r[1] = NMVectorLoad(0.0f, 2.0f / fH, 0.0f, 0.0f);
		temp.r[2] = NMVectorLoad(0.0f, 0.0f, fZTemp, 0.0f);
		temp.r[3] = NMVectorLoad(0.0f, 0.0f, -fZNear * fZTemp, 1.0f);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadPerspectiveFovLH(float fFOVY, float fAspect, float fZNear, float fZFar)
	{
		NMMatrix temp;
		float fSin, fCos;
		NMSinCos(&fSin, &fCos, fFOVY / 2.0f);
		float fYScale = fCos / fSin;
		float fXScale = fYScale / fAspect;
		float fZTemp = fZFar / (fZFar - fZNear);
		temp.r[0] = NMVectorLoad(fXScale, 0.0f, 0.0f, 0.0f);
		temp.r[1] = NMVectorLoad(0.0f, fYScale, 0.0f, 0.0f);
		temp.r[2] = NMVectorLoad(0.0f, 0.0f, fZTemp, 1.0f);
		temp.r[3] = NMVectorLoad(0.0f, 0.0f, -fZNear * fZTemp, 0.0f);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadLookAtLH(NMVectorPP eye, NMVectorPP at, NMVectorPP up)
	{
		NMMatrix result;
		NMVector zaxis = NMVector3fNormalize(NMVectorSub(at, eye));
		NMVector xaxis = NMVector3fNormalize(NMVector3fCross(up, zaxis));
		NMVector yaxis = NMVector3fCross(zaxis, xaxis);

	#ifdef _SSE_ENABLED
		zaxis = NMVector3fTrunc(zaxis);
		xaxis = NMVector3fTrunc(xaxis);
		yaxis = NMVector3fTrunc(yaxis);
		// r[0], r[1], r[2]
		result.r[0] = NMVectorAdd(NSHUFFLE(xaxis, zaxis, 0, 3, 0, 3), NSHUFFLE(yaxis, NMCVector3fOne.v, 3, 0, 3, 3));
		result.r[1] = NMVectorAdd(NSHUFFLE(xaxis, zaxis, 1, 3, 1, 3), NSHUFFLE(yaxis, NMCVector3fOne.v, 3, 1, 3, 3));
		result.r[2] = NMVectorAdd(NSHUFFLE(xaxis, zaxis, 2, 3, 2, 3), NSHUFFLE(yaxis, NMCVector3fOne.v, 3, 2, 3, 3));
		// r[3]
		NMVector xaxisDot = NMVector3fTrunc(_mm_mul_ps(xaxis, eye));
		xaxisDot = _mm_add_ss(xaxisDot, NMShuffleZWNW(xaxisDot));
		xaxisDot = _mm_add_ss(xaxisDot, NMShuffleYNNW(xaxisDot)); // 0 nan nan v

		NMVector yaxisDot = NMVector3fTrunc(_mm_mul_ps(yaxis, eye));
		yaxisDot = _mm_add_ss(yaxisDot, NMShuffleZWNW(yaxisDot));
		yaxisDot = _mm_add_ss(yaxisDot, NMShuffleYNNW(yaxisDot)); // 0 nan nan v

		NMVector zaxisDot = NMVector3fTrunc(_mm_mul_ps(zaxis, eye));
		zaxisDot = _mm_add_ss(zaxisDot, NMShuffleZWNW(zaxisDot));
		zaxisDot = _mm_add_ss(zaxisDot, NMShuffleYNNW(zaxisDot)); // 0 nan nan v

		result.r[3] = _mm_add_ps(NSHUFFLE(xaxisDot, zaxisDot, 0, 3, 0, 3), NSHUFFLE(yaxis, NMCVector3fOne.v, 3, 0, 3, 0));
		result.r[3] = _mm_mul_ps(result.r[3], NMCVector4fNegOne3One.v);
	#else
		result.r[0] = NMVectorLoad(xaxis.x, yaxis.x, zaxis.x, 0.0f);
		result.r[1] = NMVectorLoad(xaxis.y, yaxis.y, zaxis.y, 0.0f);
		result.r[2] = NMVectorLoad(xaxis.z, yaxis.z, zaxis.z, 0.0f);
		result.r[3] = NMVectorLoad(-NMVector3fDot(xaxis, eye), -NMVector3fDot(yaxis, eye), -NMVector3fDot(zaxis, eye), 1.0f);
	#endif
		return result;
	}

	_NINLINE NMMatrix NMMatrixLoadScale(float x, float y, float z)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorLoad(x, 0.0f, 0.0f, 0.0f);
		temp.r[1] = NMVectorLoad(0.0f, y, 0.0f, 0.0f);
		temp.r[2] = NMVectorLoad(0.0f, 0.0f, z, 0.0f);
		temp.r[3] = NMVectorLoad(0.0f, 0.0f, 0.0f, 1.0f);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadTranslation(float x, float y, float z)
	{
		NMMatrix temp;
		temp.r[0] = NMCVector4fIdentityRow0.v;
		temp.r[1] = NMCVector4fIdentityRow1.v;
		temp.r[2] = NMCVector4fIdentityRow2.v;
		temp.r[3] = NMVectorLoad(x, y, z, 1.0f);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadTranslation(const NMVector3f& vector)
	{
		NMMatrix temp;
		temp.r[0] = NMCVector4fIdentityRow0.v;
		temp.r[1] = NMCVector4fIdentityRow1.v;
		temp.r[2] = NMCVector4fIdentityRow2.v;
		temp.r[3] = NMVectorLoad(vector.x, vector.y, vector.z, 1.0f);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadTranslation(NMVectorPP vector)
	{
		NMMatrix temp;
		temp.r[0] = NMCVector4fIdentityRow0.v;
		temp.r[1] = NMCVector4fIdentityRow1.v;
		temp.r[2] = NMCVector4fIdentityRow2.v;
	#ifdef _SSE_ENABLED
		NMVector v = NMVector3fTrunc(vector);
		temp.r[3] = _mm_or_ps(v, NMCVector4fIdentityRow3.v);
	#else
		temp.m41 = vector.x;
		temp.m42 = vector.y;
		temp.m43 = vector.z;
		temp.m44 = 1.0f;
	#endif
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadRotationNormalizedAxis(NMVectorPP vNormalizedAxis, float fAngle)
	{
		float fSin, fCos, fOneCos;
		NMSinCos(&fSin, &fCos, -fAngle);		// Algorytm obraca w drug¹ stronê
		fOneCos = 1.0f - fCos;

		NMMatrix temp;
	#ifdef _SSE_ENABLED
		NMVector v = NMVector3fTrunc(vNormalizedAxis);
		NMVector c1 = NMVectorLoad(fOneCos);							// fOneCos
		NMVector c2 = _mm_mul_ps(NMVectorLoad(fSin), v);				// fSin * vNormalized [w = 0]
		c2 = _mm_add_ps(NMVectorLoad(0.0f, 0.0f, 0.0f, fCos), c2);		// fSin * vNormalized [w = fCos]
		// Row 0
		NMVector t1 = NMShuffleXXXW(vNormalizedAxis);							// [x, x, x, 0]
		t1 = _mm_mul_ps(c1, _mm_mul_ps(t1, v));									// fOneCos * [xx, xy, xz, 0]
		NMVector t2 = _mm_mul_ps(NMVectorLoad(0.0f, 1.0f, -1.0f, 1.0f), c2);	// [ 0.0f, fSin * y, -fSin * z, fCos]
		temp.r[0] = _mm_add_ps(t1, NMShuffleWZYX(t2));
		// Row 1
		t1 = NMShuffleYYYW(vNormalizedAxis);
		t1 = _mm_mul_ps(c1, _mm_mul_ps(t1, v));							// fOneCos * [xy, yy, yz, 0]
		t2 = _mm_mul_ps(NMVectorLoad(-1.0f, 0.0f, 1.0f, 1.0f), c2);		// fSin * vNormalized [ -x, 0.0f, z, fCos ]
		temp.r[1] = _mm_add_ps(t1, NMShuffleZWXY(t2));
		// Row 2
		t1 = NMShuffleZZZW(vNormalizedAxis);
		t1 = _mm_mul_ps(c1, _mm_mul_ps(t1, v));							// fOneCos * [xz, yz, zz, 0]
		t2 = _mm_mul_ps(NMVectorLoad(1.0f, -1.0f, 0.0f, 1.0f), c2);		// fSin * vNormalized [ x, -y, 0.0f, fCos ]
		temp.r[2] = _mm_add_ps(t1, NMShuffleYXWZ(t2));
	#else
		float fXYOneCos = vNormalizedAxis.x * vNormalizedAxis.y * fOneCos;
		float fXZOneCos = vNormalizedAxis.x * vNormalizedAxis.z * fOneCos;
		float fYZOneCos = vNormalizedAxis.y * vNormalizedAxis.z * fOneCos;
		// Row 0
		temp.m11 = vNormalizedAxis.x * vNormalizedAxis.x * fOneCos + fCos;
		temp.m12 = fXYOneCos - vNormalizedAxis.z * fSin;
		temp.m13 = fXZOneCos + vNormalizedAxis.y * fSin;
		temp.m14 = 0.0f;
		// Row 1
		temp.m21 = fXYOneCos + vNormalizedAxis.z * fSin;
		temp.m22 = vNormalizedAxis.y * vNormalizedAxis.y * fOneCos + fCos;
		temp.m23 = fYZOneCos - vNormalizedAxis.x * fSin;
		temp.m24 = 0.0f;
		// Row 2
		temp.m31 = fXZOneCos - vNormalizedAxis.y * fSin;
		temp.m32 = fYZOneCos + vNormalizedAxis.x * fSin;
		temp.m33 = vNormalizedAxis.z * vNormalizedAxis.z * fOneCos + fCos;
		temp.m34 = 0.0f;
	#endif
		// Row 3
		temp.r[3] = NMCVector4fIdentityRow3.v;
		return temp;
	}

	_NINLINE NMMatrix NMMatrixLoadRotationAxis(NMVectorPP vAxis, float fAngle)
	{
		NMVector vNormalizedAxis = NMVector3fNormalize(vAxis);
		return NMMatrixLoadRotationNormalizedAxis(vNormalizedAxis, fAngle);
	}

	_NINLINE NMMatrix NMMatrixAdd(NMMatrixPP matA, NMMatrixPP matB)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorAdd(matA.r[0], matB.r[0]);
		temp.r[1] = NMVectorAdd(matA.r[1], matB.r[1]);
		temp.r[2] = NMVectorAdd(matA.r[2], matB.r[2]);
		temp.r[3] = NMVectorAdd(matA.r[3], matB.r[3]);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixSub(NMMatrixPP matA, NMMatrixPP matB)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorSub(matA.r[0], matB.r[0]);
		temp.r[1] = NMVectorSub(matA.r[1], matB.r[1]);
		temp.r[2] = NMVectorSub(matA.r[2], matB.r[2]);
		temp.r[3] = NMVectorSub(matA.r[3], matB.r[3]);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixMul(NMMatrixPP matA, float f)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorMul(matA.r[0], f);
		temp.r[1] = NMVectorMul(matA.r[1], f);
		temp.r[2] = NMVectorMul(matA.r[2], f);
		temp.r[3] = NMVectorMul(matA.r[3], f);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixMulEach(NMMatrixPP matA, NMMatrixPP matB)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorMul(matA.r[0], matB.r[0]);
		temp.r[1] = NMVectorMul(matA.r[1], matB.r[1]);
		temp.r[2] = NMVectorMul(matA.r[2], matB.r[2]);
		temp.r[3] = NMVectorMul(matA.r[3], matB.r[3]);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixDiv(NMMatrixPP matA, float f)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorDiv(matA.r[0], f);
		temp.r[1] = NMVectorDiv(matA.r[1], f);
		temp.r[2] = NMVectorDiv(matA.r[2], f);
		temp.r[3] = NMVectorDiv(matA.r[3], f);
		return temp;
	}

	_NINLINE NMMatrix NMMatrixDivEach(NMMatrixPP matA, NMMatrixPP matB)
	{
		NMMatrix temp;
		temp.r[0] = NMVectorDiv(matA.r[0], matB.r[0]);
		temp.r[1] = NMVectorDiv(matA.r[1], matB.r[1]);
		temp.r[2] = NMVectorDiv(matA.r[2], matB.r[2]);
		temp.r[3] = NMVectorDiv(matA.r[3], matB.r[3]);
		return temp;
	}

	_NINLINE NMMatrix operator+(NMMatrixPP matA, NMMatrixPP matB)
	{
		return NMMatrixAdd(matA, matB);
	}

	_NINLINE NMMatrix operator-(NMMatrixPP matA, NMMatrixPP matB)
	{
		return NMMatrixSub(matA, matB);
	}

	_NINLINE NMMatrix operator*(NMMatrixPP matA, float f)
	{
		return NMMatrixMul(matA, f);
	}

	_NINLINE NMMatrix operator*(float f, NMMatrixPP matA)
	{
		return NMMatrixMul(matA, f);
	}

	_NINLINE NMMatrix operator*(NMMatrixPP matA, NMMatrixPP matB)
	{
		return NMMatrixMulEach(matA, matB);
	}

	_NINLINE NMMatrix operator/(NMMatrixPP matA, float f)
	{
		return NMMatrixDiv(matA, f);
	}

	NMMatrix operator/(NMMatrixPP matA, NMMatrixPP matB)
	{
		return NMMatrixDivEach(matA, matB);
	}

	_NINLINE NMMatrix& operator+=(NMMatrix& matA, NMMatrixPP matB)
	{
		matA.r[0] += matB.r[0];
		matA.r[1] += matB.r[1];
		matA.r[2] += matB.r[2];
		matA.r[3] += matB.r[3];
		return matA;
	}

	_NINLINE NMMatrix& operator-=(NMMatrix& matA, NMMatrixPP matB)
	{
		matA.r[0] -= matB.r[0];
		matA.r[1] -= matB.r[1];
		matA.r[2] -= matB.r[2];
		matA.r[3] -= matB.r[3];
		return matA;
	}

	_NINLINE NMMatrix& operator*=(NMMatrix& matA, float f)
	{
		matA.r[0] *= f;
		matA.r[1] *= f;
		matA.r[2] *= f;
		matA.r[3] *= f;
		return matA;
	}

	_NINLINE NMMatrix& operator/=(NMMatrix& matA, float f)
	{
		matA.r[0] /= f;
		matA.r[1] /= f;
		matA.r[2] /= f;
		matA.r[3] /= f;
		return matA;
	}

	_NINLINE NMMatrix NMMatrixMul(NMMatrixPP matA, NMMatrixPP matB)
	{
		NMMatrix temp;
	#ifdef _SSE_ENABLED
		// Implementacja na bazie XNAMath
		NMVector w = matA.r[0];
		NMVector x = NMShuffleXXXX(w);
		NMVector y = NMShuffleYYYY(w);
		NMVector z = NMShuffleZZZZ(w);
		w = NMShuffleWWWW(w);
		// Pierwszy wiersz
		x = _mm_mul_ps(x, matB.r[0]);
		y = _mm_mul_ps(y, matB.r[1]);
		z = _mm_mul_ps(z, matB.r[2]);
		w = _mm_mul_ps(w, matB.r[3]);
		x = _mm_add_ps(x, z);
		y = _mm_add_ps(y, w);
		x = _mm_add_ps(x, y);
		temp.r[0] = x;
		// Drugi wiersz
		w = matA.r[1];
		x = NMShuffleXXXX(w);
		y = NMShuffleYYYY(w);
		z = NMShuffleZZZZ(w);
		w = NMShuffleWWWW(w);
		x = _mm_mul_ps(x, matB.r[0]);
		y = _mm_mul_ps(y, matB.r[1]);
		z = _mm_mul_ps(z, matB.r[2]);
		w = _mm_mul_ps(w, matB.r[3]);
		x = _mm_add_ps(x, z);
		y = _mm_add_ps(y, w);
		x = _mm_add_ps(x, y);
		temp.r[1] = x;
		// Trzeci wiersz
		w = matA.r[2];
		x = NMShuffleXXXX(w);
		y = NMShuffleYYYY(w);
		z = NMShuffleZZZZ(w);
		w = NMShuffleWWWW(w);
		x = _mm_mul_ps(x, matB.r[0]);
		y = _mm_mul_ps(y, matB.r[1]);
		z = _mm_mul_ps(z, matB.r[2]);
		w = _mm_mul_ps(w, matB.r[3]);
		x = _mm_add_ps(x, z);
		y = _mm_add_ps(y, w);
		x = _mm_add_ps(x, y);
		temp.r[2] = x;
		// Czwarty wiersz
		w = matA.r[3];
		x = NMShuffleXXXX(w);
		y = NMShuffleYYYY(w);
		z = NMShuffleZZZZ(w);
		w = NMShuffleWWWW(w);
		x = _mm_mul_ps(x, matB.r[0]);
		y = _mm_mul_ps(y, matB.r[1]);
		z = _mm_mul_ps(z, matB.r[2]);
		w = _mm_mul_ps(w, matB.r[3]);
		x = _mm_add_ps(x, z);
		y = _mm_add_ps(y, w);
		x = _mm_add_ps(x, y);
		temp.r[3] = x;
	#else
		// Cache
		float x = matA.m11;
		float y = matA.m12;
		float z = matA.m13;
		float w = matA.m14;
		// Pierwszy wiersz
		temp.m11 = (matB.m11 * x) + (matB.m21 * y) + (matB.m31 * z) + (matB.m41 * w);
		temp.m12 = (matB.m12 * x) + (matB.m22 * y) + (matB.m32 * z) + (matB.m42 * w);
		temp.m13 = (matB.m13 * x) + (matB.m23 * y) + (matB.m33 * z) + (matB.m43 * w);
		temp.m14 = (matB.m14 * x) + (matB.m24 * y) + (matB.m34 * z) + (matB.m44 * w);
		// Drugi wiersz
		x = matA.m21;
		y = matA.m22;
		z = matA.m23;
		w = matA.m24;
		temp.m21 = (matB.m11 * x) + (matB.m21 * y) + (matB.m31 * z) + (matB.m41 * w);
		temp.m22 = (matB.m12 * x) + (matB.m22 * y) + (matB.m32 * z) + (matB.m42 * w);
		temp.m23 = (matB.m13 * x) + (matB.m23 * y) + (matB.m33 * z) + (matB.m43 * w);
		temp.m24 = (matB.m14 * x) + (matB.m24 * y) + (matB.m34 * z) + (matB.m44 * w);
		// Trzeci wiersz
		x = matA.m31;
		y = matA.m32;
		z = matA.m33;
		w = matA.m34;
		temp.m31 = (matB.m11 * x) + (matB.m21 * y) + (matB.m31 * z) + (matB.m41 * w);
		temp.m32 = (matB.m12 * x) + (matB.m22 * y) + (matB.m32 * z) + (matB.m42 * w);
		temp.m33 = (matB.m13 * x) + (matB.m23 * y) + (matB.m33 * z) + (matB.m43 * w);
		temp.m34 = (matB.m14 * x) + (matB.m24 * y) + (matB.m34 * z) + (matB.m44 * w);
		// Czwarty
		x = matA.m41;
		y = matA.m42;
		z = matA.m43;
		w = matA.m44;
		temp.m41 = (matB.m11 * x) + (matB.m21 * y) + (matB.m31 * z) + (matB.m41 * w);
		temp.m42 = (matB.m12 * x) + (matB.m22 * y) + (matB.m32 * z) + (matB.m42 * w);
		temp.m43 = (matB.m13 * x) + (matB.m23 * y) + (matB.m33 * z) + (matB.m43 * w);
		temp.m44 = (matB.m14 * x) + (matB.m24 * y) + (matB.m34 * z) + (matB.m44 * w);
	#endif
		return temp;
	}

	_NINLINE NMMatrix NMMatrixTranspose(NMMatrixPP mat)
	{
		NMMatrix temp;
	#ifdef _SSE_ENABLED
		temp = mat;
		_MM_TRANSPOSE4_PS(temp.r[0], temp.r[1], temp.r[2], temp.r[3]);
	#else
		temp.m11 = mat.m11; temp.m12 = mat.m21;	temp.m13 = mat.m31;	temp.m14 = mat.m41;
		temp.m21 = mat.m12;	temp.m22 = mat.m22; temp.m23 = mat.m32;	temp.m24 = mat.m42;
		temp.m31 = mat.m13;	temp.m32 = mat.m23;	temp.m33 = mat.m33; temp.m34 = mat.m43;
		temp.m41 = mat.m14; temp.m42 = mat.m24; temp.m43 = mat.m34; temp.m44 = mat.m44;
	#endif
		return temp;
	}

	_NINLINE float NMMatrixDeterminant(NMMatrixPP mat)
	{
		float fResult;
	#ifdef _SSE_ENABLED
		NMVector RS[9], temp[2];
		RS[0] = NMShuffleYXWZ(mat.r[1]);
		RS[1] = NMShuffleZWXY(mat.r[1]);
		RS[2] = NMShuffleWZYX(mat.r[1]);
		RS[3] = NMShuffleZWXY(mat.r[2]);
		RS[4] = NMShuffleWZYX(mat.r[2]);
		RS[5] = NMShuffleYXWZ(mat.r[2]);
		RS[6] = NMShuffleWZYX(mat.r[3]);
		RS[7] = NMShuffleZWXY(mat.r[3]);
		RS[8] = NMShuffleYXWZ(mat.r[3]);

		temp[0] = NMVectorMul(NMVectorMul(NMVectorMul(mat.r[0], RS[0]), RS[3]), RS[6]);
		temp[1] = NMVectorMul(NMVectorMul(NMVectorMul(mat.r[0], RS[0]), RS[4]), RS[7]);
		temp[0] = NMVectorSub(temp[0], temp[1]);
		temp[1] = NMVectorMul(NMVectorMul(NMVectorMul(mat.r[0], RS[1]), RS[5]), RS[6]);
		temp[0] = NMVectorSub(temp[0], temp[1]);
		temp[1] = NMVectorMul(NMVectorMul(NMVectorMul(mat.r[0], RS[1]), RS[4]), RS[8]);
		temp[0] = NMVectorAdd(temp[0], temp[1]);
		temp[1] = NMVectorMul(NMVectorMul(NMVectorMul(mat.r[0], RS[2]), RS[5]), RS[7]);
		temp[0] = NMVectorAdd(temp[0], temp[1]);
		temp[1] = NMVectorMul(NMVectorMul(NMVectorMul(mat.r[0], RS[2]), RS[3]), RS[8]);
		temp[0] = NMVectorSub(temp[0], temp[1]);

		temp[0] = _mm_add_ps(temp[0], NMShuffleWZNN(temp[0]));	 // [ n n y+z x+w ]
		temp[0] = _mm_add_ss(temp[0], NMShuffleYNNN(temp[0]));   // [ n n n x+y+z+w ]
		_mm_store_ss(&fResult, temp[0]);
	#else
		float f22d[6];
		f22d[0] = mat.m33 * mat.m44 - mat.m34 * mat.m43;
		f22d[1] = mat.m32 * mat.m44 - mat.m34 * mat.m42;
		f22d[2] = mat.m32 * mat.m43 - mat.m33 * mat.m42;
		f22d[3] = mat.m31 * mat.m44 - mat.m34 * mat.m41;
		f22d[4] = mat.m31 * mat.m43 - mat.m33 * mat.m41;
		f22d[5] = mat.m31 * mat.m42 - mat.m32 * mat.m41;

		fResult  = mat.m11 * (mat.m22 * f22d[0] - mat.m23 * f22d[1] + mat.m24 * f22d[2]);
		fResult -= mat.m12 * (mat.m21 * f22d[0] - mat.m23 * f22d[3] + mat.m24 * f22d[4]);
		fResult += mat.m13 * (mat.m21 * f22d[1] - mat.m22 * f22d[3] + mat.m24 * f22d[5]);
		fResult -= mat.m14 * (mat.m21 * f22d[2] - mat.m22 * f22d[4] + mat.m23 * f22d[5]);
	#endif
		return fResult;
	}

	_NINLINE NMMatrix NMMatrixInverse(NMMatrixPP mat, float* opfDeterminant)
	{
		// This function is copied from xnamathmatrix.inl from DirectX SDK June 2010
		NMMatrix result;
	#ifdef _SSE_ENABLED
		NMMatrix MT = NMMatrixTranspose(mat);
		NMVector V00 = _mm_shuffle_ps(MT.r[2], MT.r[2],_MM_SHUFFLE(1,1,0,0));
		NMVector V10 = _mm_shuffle_ps(MT.r[3], MT.r[3],_MM_SHUFFLE(3,2,3,2));
		NMVector V01 = _mm_shuffle_ps(MT.r[0], MT.r[0],_MM_SHUFFLE(1,1,0,0));
		NMVector V11 = _mm_shuffle_ps(MT.r[1], MT.r[1],_MM_SHUFFLE(3,2,3,2));
		NMVector V02 = _mm_shuffle_ps(MT.r[2], MT.r[0],_MM_SHUFFLE(2,0,2,0));
		NMVector V12 = _mm_shuffle_ps(MT.r[3], MT.r[1],_MM_SHUFFLE(3,1,3,1));

		NMVector D0 = _mm_mul_ps(V00,V10);
		NMVector D1 = _mm_mul_ps(V01,V11);
		NMVector D2 = _mm_mul_ps(V02,V12);

		V00 = _mm_shuffle_ps(MT.r[2],MT.r[2],_MM_SHUFFLE(3,2,3,2));
		V10 = _mm_shuffle_ps(MT.r[3],MT.r[3],_MM_SHUFFLE(1,1,0,0));
		V01 = _mm_shuffle_ps(MT.r[0],MT.r[0],_MM_SHUFFLE(3,2,3,2));
		V11 = _mm_shuffle_ps(MT.r[1],MT.r[1],_MM_SHUFFLE(1,1,0,0));
		V02 = _mm_shuffle_ps(MT.r[2],MT.r[0],_MM_SHUFFLE(3,1,3,1));
		V12 = _mm_shuffle_ps(MT.r[3],MT.r[1],_MM_SHUFFLE(2,0,2,0));

		V00 = _mm_mul_ps(V00,V10);
		V01 = _mm_mul_ps(V01,V11);
		V02 = _mm_mul_ps(V02,V12);
		D0 = _mm_sub_ps(D0,V00);
		D1 = _mm_sub_ps(D1,V01);
		D2 = _mm_sub_ps(D2,V02);
		// V11 = D0Y,D0W,D2Y,D2Y
		V11 = _mm_shuffle_ps(D0,D2,_MM_SHUFFLE(1,1,3,1));
		V00 = _mm_shuffle_ps(MT.r[1], MT.r[1],_MM_SHUFFLE(1,0,2,1));
		V10 = _mm_shuffle_ps(V11,D0,_MM_SHUFFLE(0,3,0,2));
		V01 = _mm_shuffle_ps(MT.r[0], MT.r[0],_MM_SHUFFLE(0,1,0,2));
		V11 = _mm_shuffle_ps(V11,D0,_MM_SHUFFLE(2,1,2,1));
		// V13 = D1Y,D1W,D2W,D2W
		NMVector V13 = _mm_shuffle_ps(D1,D2,_MM_SHUFFLE(3,3,3,1));
		V02 = _mm_shuffle_ps(MT.r[3], MT.r[3],_MM_SHUFFLE(1,0,2,1));
		V12 = _mm_shuffle_ps(V13,D1,_MM_SHUFFLE(0,3,0,2));
		NMVector V03 = _mm_shuffle_ps(MT.r[2], MT.r[2],_MM_SHUFFLE(0,1,0,2));
		V13 = _mm_shuffle_ps(V13,D1,_MM_SHUFFLE(2,1,2,1));

		NMVector C0 = _mm_mul_ps(V00,V10);
		NMVector C2 = _mm_mul_ps(V01,V11);
		NMVector C4 = _mm_mul_ps(V02,V12);
		NMVector C6 = _mm_mul_ps(V03,V13);

		// V11 = D0X,D0Y,D2X,D2X
		V11 = _mm_shuffle_ps(D0,D2,_MM_SHUFFLE(0,0,1,0));
		V00 = _mm_shuffle_ps(MT.r[1], MT.r[1],_MM_SHUFFLE(2,1,3,2));
		V10 = _mm_shuffle_ps(D0,V11,_MM_SHUFFLE(2,1,0,3));
		V01 = _mm_shuffle_ps(MT.r[0], MT.r[0],_MM_SHUFFLE(1,3,2,3));
		V11 = _mm_shuffle_ps(D0,V11,_MM_SHUFFLE(0,2,1,2));
		// V13 = D1X,D1Y,D2Z,D2Z
		V13 = _mm_shuffle_ps(D1,D2,_MM_SHUFFLE(2,2,1,0));
		V02 = _mm_shuffle_ps(MT.r[3], MT.r[3],_MM_SHUFFLE(2,1,3,2));
		V12 = _mm_shuffle_ps(D1,V13,_MM_SHUFFLE(2,1,0,3));
		V03 = _mm_shuffle_ps(MT.r[2], MT.r[2],_MM_SHUFFLE(1,3,2,3));
		V13 = _mm_shuffle_ps(D1,V13,_MM_SHUFFLE(0,2,1,2));

		V00 = _mm_mul_ps(V00,V10);
		V01 = _mm_mul_ps(V01,V11);
		V02 = _mm_mul_ps(V02,V12);
		V03 = _mm_mul_ps(V03,V13);
		C0 = _mm_sub_ps(C0,V00);
		C2 = _mm_sub_ps(C2,V01);
		C4 = _mm_sub_ps(C4,V02);
		C6 = _mm_sub_ps(C6,V03);

		V00 = _mm_shuffle_ps(MT.r[1],MT.r[1],_MM_SHUFFLE(0,3,0,3));
		// V10 = D0Z,D0Z,D2X,D2Y
		V10 = _mm_shuffle_ps(D0,D2,_MM_SHUFFLE(1,0,2,2));
		V10 = _mm_shuffle_ps(V10,V10,_MM_SHUFFLE(0,2,3,0));
		V01 = _mm_shuffle_ps(MT.r[0],MT.r[0],_MM_SHUFFLE(2,0,3,1));
		// V11 = D0X,D0W,D2X,D2Y
		V11 = _mm_shuffle_ps(D0,D2,_MM_SHUFFLE(1,0,3,0));
		V11 = _mm_shuffle_ps(V11,V11,_MM_SHUFFLE(2,1,0,3));
		V02 = _mm_shuffle_ps(MT.r[3],MT.r[3],_MM_SHUFFLE(0,3,0,3));
		// V12 = D1Z,D1Z,D2Z,D2W
		V12 = _mm_shuffle_ps(D1,D2,_MM_SHUFFLE(3,2,2,2));
		V12 = _mm_shuffle_ps(V12,V12,_MM_SHUFFLE(0,2,3,0));
		V03 = _mm_shuffle_ps(MT.r[2],MT.r[2],_MM_SHUFFLE(2,0,3,1));
		// V13 = D1X,D1W,D2Z,D2W
		V13 = _mm_shuffle_ps(D1,D2,_MM_SHUFFLE(3,2,3,0));
		V13 = _mm_shuffle_ps(V13,V13,_MM_SHUFFLE(2,1,0,3));

		V00 = _mm_mul_ps(V00,V10);
		V01 = _mm_mul_ps(V01,V11);
		V02 = _mm_mul_ps(V02,V12);
		V03 = _mm_mul_ps(V03,V13);
		NMVector C1 = _mm_sub_ps(C0,V00);
		C0 = _mm_add_ps(C0,V00);
		NMVector C3 = _mm_add_ps(C2,V01);
		C2 = _mm_sub_ps(C2,V01);
		NMVector C5 = _mm_sub_ps(C4,V02);
		C4 = _mm_add_ps(C4,V02);
		NMVector C7 = _mm_add_ps(C6,V03);
		C6 = _mm_sub_ps(C6,V03);

		C0 = _mm_shuffle_ps(C0,C1,_MM_SHUFFLE(3,1,2,0));
		C2 = _mm_shuffle_ps(C2,C3,_MM_SHUFFLE(3,1,2,0));
		C4 = _mm_shuffle_ps(C4,C5,_MM_SHUFFLE(3,1,2,0));
		C6 = _mm_shuffle_ps(C6,C7,_MM_SHUFFLE(3,1,2,0));
		C0 = _mm_shuffle_ps(C0,C0,_MM_SHUFFLE(3,1,2,0));
		C2 = _mm_shuffle_ps(C2,C2,_MM_SHUFFLE(3,1,2,0));
		C4 = _mm_shuffle_ps(C4,C4,_MM_SHUFFLE(3,1,2,0));
		C6 = _mm_shuffle_ps(C6,C6,_MM_SHUFFLE(3,1,2,0));
		// Get the determinate
		NMVector temp = _mm_mul_ps(C0, MT.r[0]);
		temp = _mm_add_ps(temp, NMShuffleYXWZ(temp));	// [ w+z z+w y+x x+y ]
		temp = _mm_add_ps(temp, NMShuffleWZYX(temp));	// [ w+z+x+y z+w+y+x y+x+z+w x+y+z+w ]

		if(opfDeterminant != null)
		{
			_mm_store_ss(opfDeterminant, temp);
		}

		temp = _mm_div_ps(NMVectorLoad(1.0f, 1.0f, 1.0f, 1.0f), temp);

		result.r[0] = _mm_mul_ps(C0,temp);
		result.r[1] = _mm_mul_ps(C2,temp);
		result.r[2] = _mm_mul_ps(C4,temp);
		result.r[3] = _mm_mul_ps(C6,temp);
	#else
		float f22d[18];
		f22d[0] = mat.m33 * mat.m44 - mat.m34 * mat.m43;
		f22d[1] = mat.m32 * mat.m44 - mat.m34 * mat.m42;
		f22d[2] = mat.m32 * mat.m43 - mat.m33 * mat.m42;
		f22d[3] = mat.m23 * mat.m44 - mat.m24 * mat.m43;
		f22d[4] = mat.m22 * mat.m44 - mat.m24 * mat.m42;
		f22d[5] = mat.m22 * mat.m43 - mat.m23 * mat.m42;
		f22d[6] = mat.m23 * mat.m34 - mat.m24 * mat.m33;
		f22d[7] = mat.m22 * mat.m34 - mat.m24 * mat.m32;
		f22d[8] = mat.m22 * mat.m33 - mat.m23 * mat.m32;
		f22d[9] = mat.m31 * mat.m44 - mat.m34 * mat.m41;
		f22d[10] = mat.m31 * mat.m43 - mat.m33 * mat.m41;
		f22d[11] = mat.m31 * mat.m42 - mat.m32 * mat.m41;
		f22d[12] = mat.m21 * mat.m44 - mat.m24 * mat.m41;
		f22d[13] = mat.m21 * mat.m43 - mat.m23 * mat.m41;
		f22d[14] = mat.m21 * mat.m34 - mat.m24 * mat.m31;
		f22d[15] = mat.m21 * mat.m33 - mat.m23 * mat.m31;
		f22d[16] = mat.m21 * mat.m42 - mat.m22 * mat.m41;
		f22d[17] = mat.m21 * mat.m32 - mat.m22 * mat.m31;

		result.m11 =  mat.m22 * f22d[0] - mat.m23 * f22d[1] + mat.m24 * f22d[2];
		result.m12 = -mat.m12 * f22d[0] + mat.m13 * f22d[1] - mat.m14 * f22d[2];
		result.m13 =  mat.m12 * f22d[3] - mat.m13 * f22d[4] + mat.m14 * f22d[5];
		result.m14 = -mat.m12 * f22d[6] + mat.m13 * f22d[7] - mat.m14 * f22d[8];

		result.m21 = -mat.m21 * f22d[0] + mat.m23 * f22d[9]  - mat.m24 * f22d[10];
		result.m22 =  mat.m11 * f22d[0] - mat.m13 * f22d[9]  + mat.m14 * f22d[10];
		result.m23 = -mat.m11 * f22d[3] + mat.m13 * f22d[12] - mat.m14 * f22d[13];
		result.m24 =  mat.m11 * f22d[6] - mat.m13 * f22d[14] + mat.m14 * f22d[15];

		result.m31 =  mat.m21 * f22d[1] - mat.m22 * f22d[9]  + mat.m24 * f22d[11];
		result.m32 = -mat.m11 * f22d[1] + mat.m12 * f22d[9]  - mat.m14 * f22d[11];
		result.m33 =  mat.m11 * f22d[4] - mat.m12 * f22d[12] + mat.m14 * f22d[16];
		result.m34 = -mat.m11 * f22d[7] + mat.m12 * f22d[14] - mat.m14 * f22d[17];

		result.m41 = -mat.m21 * f22d[2] + mat.m22 * f22d[10] - mat.m23 * f22d[11];
		result.m42 =  mat.m11 * f22d[2] - mat.m12 * f22d[10] + mat.m13 * f22d[11];
		result.m43 = -mat.m11 * f22d[5] + mat.m12 * f22d[13] - mat.m13 * f22d[16];
		result.m44 =  mat.m11 * f22d[8] - mat.m12 * f22d[15] + mat.m13 * f22d[17];

		float fDeterminant = NMVector4fDot(result.r[0], NMVectorLoad(mat.m11, mat.m21, mat.m31, mat.m41));
		if(opfDeterminant != null)
		{
			*opfDeterminant = fDeterminant;
		}

		result = NMMatrixMul(result, 1.0f / fDeterminant);
	#endif
		return result;
	}
}
}