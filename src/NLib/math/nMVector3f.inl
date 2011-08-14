#pragma once
// Included in nMath.hpp

namespace NIne
{
	/****************************************************/
	// Declarations
	_NINLINE NMVector3f NMVector3fLoad(const float* pFloats);
	_NINLINE NMVector3f NMVector3fLoad(float f);
	_NINLINE NMVector3f NMVector3fLoad(const NMVector2f& vec);
	_NINLINE NMVector3f NMVector3fLoad(float x, float y);
	_NINLINE NMVector3f NMVector3fLoad(float x, float y, float z);

	_NINLINE NMVector3f NMVector3fLoadZeros();

	_NINLINE NMVector3f NMVector3fAdd(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fSub(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fMul(const NMVector3f& vecA, float f);
	_NINLINE NMVector3f NMVector3fMul(float f, const NMVector3f& vecA);
	_NINLINE NMVector3f NMVector3fMul(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fDiv(const NMVector3f& vecA, float f);
	_NINLINE NMVector3f NMVector3fDiv(const NMVector3f& vecA, const NMVector3f& vecB);

	_NINLINE NMVector3f NMVector3fMin(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fMax(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fAbs(const NMVector3f& vec);
	_NINLINE NMVector3f NMVector3fNeg(const NMVector3f& vec);

	_NINLINE NMVector3f NMVector3fAnd(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fAndNot(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fOr(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fNot(const NMVector3f& vecv);

	_NINLINE NMVector3f NMVector3fGreater(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fLess(const NMVector3f& vecA, const NMVector3f& vecB);

	_NINLINE NMVector3f operator+(const NMVector3f& vec);
	_NINLINE NMVector3f operator-(const NMVector3f& vec);
	_NINLINE NMVector3f operator+(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f operator-(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f operator*(const NMVector3f& vecA, float f);
	_NINLINE NMVector3f operator*(float f, const NMVector3f& vecA);
	_NINLINE NMVector3f operator*(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f operator/(const NMVector3f& vecA, float f);
	_NINLINE NMVector3f operator/(const NMVector3f& vecA, const NMVector3f& vecB);
	
	_NINLINE NMVector3f& operator+=(NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f& operator-=(NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f& operator*=(NMVector3f& vecA, float f);
	_NINLINE NMVector3f& operator/=(NMVector3f& vecA, float f);

	_NINLINE NMVector3f operator&(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f operator|(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f operator~(const NMVector3f& vec);

	_NINLINE NMVector3f operator>(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f operator<(const NMVector3f& vecA, const NMVector3f& vecB);

	_NINLINE float NMVector3fLength(const NMVector3f& vec);
	_NINLINE float NMVector3fDot(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fCross(const NMVector3f& vecA, const NMVector3f& vecB);
	_NINLINE NMVector3f NMVector3fNormalize(const NMVector3f& vec);
	_NINLINE NMVector3f NMVector3fReflect(const NMVector3f& vec, const NMVector3f& normal);
	_NINLINE NMVector3f NMVector3fReflectNormalized(const NMVector3f& vec, const NMVector3f& normal);

	/****************************************************/
	// Definitions
	_NINLINE NMVector3f NMVector3fLoad(const float* pFloats)
	{
		NMVector3f temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&pFloats[0]))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&pFloats[1]))[0];
		((NUint32*)&temp.z)[0] = ((const NUint32*)(&pFloats[2]))[0];
		return temp;
	}

	_NINLINE NMVector3f NMVector3fLoad(float f)
	{
		NMVector3f temp;
		temp.x = f;
		temp.y = f;
		temp.z = f;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fLoad(const NMVector2f& vec)
	{
		NMVector3f temp;
		temp.x = vec.x;
		temp.y = vec.y;
		temp.z = 0.0f;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fLoad(float x, float y)
	{
		NMVector3f temp;
		temp.x = x;
		temp.y = y;
		temp.z = 0.0f;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fLoad(float x, float y, float z)
	{
		NMVector3f temp;
		temp.x = x;
		temp.y = y;
		temp.z = z;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fLoadZeros()
	{
		NMVector3f temp;
		((NUint32*)&temp.x)[0] = 0;
		((NUint32*)&temp.y)[0] = 0;
		((NUint32*)&temp.z)[0] = 0;
		return temp;
	}

	_NINLINE void NMVector3fStore(float* pFloats, const NMVector3f& vec)
	{
		((NUint32*)&pFloats[0])[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&pFloats[1])[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&pFloats[2])[0] = ((const NUint32*)(&vec.z))[0];
	}

	_NINLINE NMVector3f NMVector3fAdd(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		temp.x = vecA.x + vecB.x;
		temp.y = vecA.y + vecB.y;
		temp.z = vecA.z + vecB.z;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fSub(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		temp.x = vecA.x - vecB.x;
		temp.y = vecA.y - vecB.y;
		temp.z = vecA.z - vecB.z;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fMul(const NMVector3f& vecA, float f)
	{
		NMVector3f temp;
		temp.x = vecA.x * f;
		temp.y = vecA.y * f;
		temp.z = vecA.z * f;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fMul(float f, const NMVector3f& vecA)
	{
		return NMVector3fMul(vecA, f);
	}

	_NINLINE NMVector3f NMVector3fMul(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		temp.x = vecA.x * vecB.x;
		temp.y = vecA.y * vecB.y;
		temp.z = vecA.z * vecB.z;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fDiv(const NMVector3f& vecA, float f)
	{
		NMVector3f temp;
		temp.x = vecA.x / f;
		temp.y = vecA.y / f;
		temp.z = vecA.z / f;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fDiv(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		temp.x = vecA.x / vecB.x;
		temp.y = vecA.y / vecB.y;
		temp.z = vecA.z / vecB.z;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fMin(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		temp.x = min(vecA.x, vecB.x);
		temp.y = min(vecA.y, vecB.y);
		temp.z = min(vecA.z, vecB.z);
		return temp;
	}

	_NINLINE NMVector3f NMVector3fMax(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		temp.x = max(vecA.x, vecB.x);
		temp.y = max(vecA.y, vecB.y);
		temp.z = max(vecA.z, vecB.z);
		return temp;
	}

	_NINLINE NMVector3f NMVector3fAbs(const NMVector3f& vec)
	{
		return NMVector3fMax(vec, NMVector3fNeg(vec));
	}

	_NINLINE NMVector3f NMVector3fNeg(const NMVector3f& vec)
	{
		return NMVector3fSub(NMVector3fLoadZeros(), vec);
	}

	_NINLINE NMVector3f NMVector3fAnd(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		((NUint32*)&temp.x)[0] = ((NUint32*)&vecA.x)[0] & ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ((NUint32*)&vecA.y)[0] & ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ((NUint32*)&vecA.z)[0] & ((NUint32*)&vecB.z)[0];
		return temp;
	}

	_NINLINE NMVector3f NMVector3fAndNot(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		((NUint32*)&temp.x)[0] = ~((NUint32*)&vecA.x)[0] & ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ~((NUint32*)&vecA.y)[0] & ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ~((NUint32*)&vecA.z)[0] & ((NUint32*)&vecB.z)[0];
		return temp;
	}

	_NINLINE NMVector3f NMVector3fOr(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		((NUint32*)&temp.x)[0] = ((NUint32*)&vecA.x)[0] | ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ((NUint32*)&vecA.y)[0] | ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ((NUint32*)&vecA.z)[0] | ((NUint32*)&vecB.z)[0];
		return temp;
	}

	_NINLINE NMVector3f NMVector3fNot(const NMVector3f& vec)
	{
		NMVector3f temp;
		((NUint32*)&temp.x)[0] = ~((NUint32*)&vec.x)[0];
		((NUint32*)&temp.y)[0] = ~((NUint32*)&vec.y)[0];
		((NUint32*)&temp.z)[0] = ~((NUint32*)&vec.z)[0];
		return temp;
	}

	_NINLINE NMVector3f NMVector3fGreater(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		((NUint32*)&temp.x)[0] = vecA.x > vecB.x ? 0xffffffff : 0x0;
		((NUint32*)&temp.y)[0] = vecA.y > vecB.y ? 0xffffffff : 0x0;
		((NUint32*)&temp.z)[0] = vecA.z > vecB.z ? 0xffffffff : 0x0;
		return temp;
	}

	_NINLINE NMVector3f NMVector3fLess(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		((NUint32*)&temp.x)[0] = vecA.x < vecB.x ? 0xffffffff : 0x0;
		((NUint32*)&temp.y)[0] = vecA.y < vecB.y ? 0xffffffff : 0x0;
		((NUint32*)&temp.z)[0] = vecA.z < vecB.z ? 0xffffffff : 0x0;
		return temp;
	}

	_NINLINE NMVector3f operator+(const NMVector3f& vec)
	{
		return vec;
	}

	_NINLINE NMVector3f operator-(const NMVector3f& vec)
	{
		return NMVector3fNeg(vec);
	}

	_NINLINE NMVector3f operator+(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		return NMVector3fAdd(vecA, vecB);
	}

	_NINLINE NMVector3f operator-(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		return NMVector3fSub(vecA, vecB);
	}

	_NINLINE NMVector3f operator*(const NMVector3f& vecA, float f)
	{
		return NMVector3fMul(vecA, f);
	}

	_NINLINE NMVector3f operator*(float f, const NMVector3f& vecA)
	{
		return NMVector3fMul(vecA, f);
	}

	_NINLINE NMVector3f operator*(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		return NMVector3fMul(vecA, vecB);
	}

	_NINLINE NMVector3f operator/(const NMVector3f& vecA, float f)
	{
		return NMVector3fDiv(vecA, f);
	}

	_NINLINE NMVector3f operator/(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		return NMVector3fDiv(vecA, vecB);
	}

	_NINLINE NMVector3f operator&(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		return NMVector3fAnd(vecA, vecB);
	}

	_NINLINE NMVector3f operator|(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		return NMVector3fOr(vecA, vecB);
	}

	_NINLINE NMVector3f operator~(const NMVector3f& vec)
	{
		return NMVector3fNot(vec);
	}

	_NINLINE NMVector3f operator>(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		return NMVector3fGreater(vecA, vecB);
	}

	_NINLINE NMVector3f operator<(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		return NMVector3fLess(vecA, vecB);
	}
	
	_NINLINE NMVector3f& operator+=(NMVector3f& vecA, const NMVector3f& vecB)
	{
		vecA.x += vecB.x;
		vecA.y += vecB.y;
		vecA.z += vecB.z;
		return vecA;
	}

	_NINLINE NMVector3f& operator-=(NMVector3f& vecA, const NMVector3f& vecB)
	{
		vecA.x -= vecB.x;
		vecA.y -= vecB.y;
		vecA.z -= vecB.z;
		return vecA;
	}

	_NINLINE NMVector3f& operator*=(NMVector3f& vecA, float f)
	{
		vecA.x *= f;
		vecA.y *= f;
		vecA.z *= f;
		return vecA;
	}

	_NINLINE NMVector3f& operator*=(NMVector3f& vecA, const NMVector3f& vecB)
	{
		vecA.x *= vecB.x;
		vecA.y *= vecB.y;
		vecA.z *= vecB.z;
		return vecA;
	}

	_NINLINE NMVector3f& operator/=(NMVector3f& vecA, float f)
	{
		vecA.x /= f;
		vecA.y /= f;
		vecA.z /= f;
		return vecA;
	}

	_NINLINE NMVector3f& operator/=(NMVector3f& vecA, const NMVector3f& vecB)
	{
		vecA.x /= vecB.x;
		vecA.y /= vecB.y;
		vecA.z /= vecB.z;
		return vecA;
	}

	_NINLINE float NMVector3fDot(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		float f;
		f = vecA.x * vecB.x;
		f += vecA.y * vecB.y;
		f += vecA.z * vecB.z;
		return f;
	}

	_NINLINE NMVector3f NMVector3fCross(const NMVector3f& vecA, const NMVector3f& vecB)
	{
		NMVector3f temp;
		temp.x = vecA.y * vecB.z - vecA.z * vecB.y;
		temp.y = vecA.z * vecB.x - vecA.x * vecB.z;
		temp.z = vecA.x * vecB.y - vecA.y * vecB.x;
		return temp;
	}

	_NINLINE float NMVector3fLength(const NMVector3f& vec)
	{
		return sqrt(NMVector3fDot(vec, vec));
	}

	_NINLINE NMVector3f NMVector3fNormalize(const NMVector3f& vec)
	{
		return NMVector3fDiv(vec, NMVector3fLength(vec));
	}

	_NINLINE NMVector3f NMVector3fReflect(const NMVector3f& vec, const NMVector3f& normal)
	{
		return vec - NMVector3fMul(normal, 2 * NMVector3fDot(vec, normal));
	}

	_NINLINE NMVector3f NMVector3fReflectNormalized(const NMVector3f& vec, const NMVector3f& normal)
	{
		return vec - NMVector3fMul(normal, 2 * NMVector3fDot(vec, normal) / NMVector3fDot(normal, normal));
	}
}