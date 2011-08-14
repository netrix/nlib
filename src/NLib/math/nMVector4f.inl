#pragma once
// Included in nMath.hpp

namespace NIne
{
	/****************************************************/
	// Declarations
	_NINLINE NMVector4f NMVector4fLoad(const float* pFloats);
	_NINLINE NMVector4f NMVector4fLoad(float f);
	_NINLINE NMVector4f NMVector4fLoad(float x, float y);
	_NINLINE NMVector4f NMVector4fLoad(float x, float y, float z);
	_NINLINE NMVector4f NMVector4fLoad(float x, float y, float z, float w);

	_NINLINE NMVector4f NMVector4fLoadZeros();

	_NINLINE NMVector4f NMVector4fAdd(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fSub(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fMul(const NMVector4f& vecA, float f);
	_NINLINE NMVector4f NMVector4fMul(float f, const NMVector4f& vecA);
	_NINLINE NMVector4f NMVector4fMul(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fDiv(const NMVector4f& vecA, float f);
	_NINLINE NMVector4f NMVector4fDiv(const NMVector4f& vecA, const NMVector4f& vecB);

	_NINLINE NMVector4f NMVector4fMin(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fMax(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fAbs(const NMVector4f& vec);
	_NINLINE NMVector4f NMVector4fNeg(const NMVector4f& vec);

	_NINLINE NMVector4f NMVector4fAnd(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fAndNot(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fOr(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fNot(const NMVector4f& vecv);

	_NINLINE NMVector4f NMVector4fGreater(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fLess(const NMVector4f& vecA, const NMVector4f& vecB);

	_NINLINE NMVector4f operator+(const NMVector4f& vec);
	_NINLINE NMVector4f operator-(const NMVector4f& vec);
	_NINLINE NMVector4f operator+(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f operator-(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f operator*(const NMVector4f& vecA, float f);
	_NINLINE NMVector4f operator*(float f, const NMVector4f& vecA);
	_NINLINE NMVector4f operator*(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f operator/(const NMVector4f& vecA, float f);
	_NINLINE NMVector4f operator/(const NMVector4f& vecA, const NMVector4f& vecB);
	
	_NINLINE NMVector4f& operator+=(NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f& operator-=(NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f& operator*=(NMVector4f& vecA, float f);
	_NINLINE NMVector4f& operator/=(NMVector4f& vecA, float f);

	_NINLINE NMVector4f operator&(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f operator|(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f operator~(const NMVector4f& vec);

	_NINLINE NMVector4f operator>(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f operator<(const NMVector4f& vecA, const NMVector4f& vecB);

	_NINLINE float NMVector4fLength(const NMVector4f& vec);
	_NINLINE float NMVector4fDot(const NMVector4f& vecA, const NMVector4f& vecB);
	_NINLINE NMVector4f NMVector4fNormalize(const NMVector4f& vec);

	/****************************************************/
	// Definitions
	_NINLINE NMVector4f NMVector4fLoad(const float* pFloats)
	{
		NMVector4f temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&pFloats[0]))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&pFloats[1]))[0];
		((NUint32*)&temp.z)[0] = ((const NUint32*)(&pFloats[2]))[0];
		((NUint32*)&temp.w)[0] = ((const NUint32*)(&pFloats[3]))[0];
		return temp;
	}

	_NINLINE NMVector4f NMVector4fLoad(float f)
	{
		NMVector4f temp;
		temp.x = f;
		temp.y = f;
		temp.z = f;
		temp.w = f;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fLoad(float x, float y)
	{
		NMVector4f temp;
		temp.x = x;
		temp.y = y;
		temp.z = 0.0f;
		temp.w = 0.0f;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fLoad(float x, float y, float z)
	{
		NMVector4f temp;
		temp.x = x;
		temp.y = y;
		temp.z = z;
		temp.w = 0.0f;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fLoad(float x, float y, float z, float w)
	{
		NMVector4f temp;
		temp.x = x;
		temp.y = y;
		temp.z = z;
		temp.w = w;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fLoadZeros()
	{
		NMVector4f temp;
		((NUint32*)&temp.x)[0] = 0;
		((NUint32*)&temp.y)[0] = 0;
		((NUint32*)&temp.z)[0] = 0;
		((NUint32*)&temp.w)[0] = 0;
		return temp;
	}

	_NINLINE void NMVector4fStore(float* pFloats, const NMVector4f& vec)
	{
		((NUint32*)&pFloats[0])[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&pFloats[1])[0] = ((const NUint32*)(&vec.y))[0];
		((NUint32*)&pFloats[2])[0] = ((const NUint32*)(&vec.z))[0];
		((NUint32*)&pFloats[3])[0] = ((const NUint32*)(&vec.w))[0];
	}

	_NINLINE NMVector4f NMVector4fAdd(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		temp.x = vecA.x + vecB.x;
		temp.y = vecA.y + vecB.y;
		temp.z = vecA.z + vecB.z;
		temp.w = vecA.w + vecB.w;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fSub(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		temp.x = vecA.x - vecB.x;
		temp.y = vecA.y - vecB.y;
		temp.z = vecA.z - vecB.z;
		temp.w = vecA.w - vecB.w;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fMul(const NMVector4f& vecA, float f)
	{
		NMVector4f temp;
		temp.x = vecA.x * f;
		temp.y = vecA.y * f;
		temp.z = vecA.z * f;
		temp.w = vecA.w * f;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fMul(float f, const NMVector4f& vecA)
	{
		return NMVector4fMul(vecA, f);
	}

	_NINLINE NMVector4f NMVector4fMul(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		temp.x = vecA.x * vecB.x;
		temp.y = vecA.y * vecB.y;
		temp.z = vecA.z * vecB.z;
		temp.w = vecA.w * vecB.w;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fDiv(const NMVector4f& vecA, float f)
	{
		NMVector4f temp;
		temp.x = vecA.x / f;
		temp.y = vecA.y / f;
		temp.z = vecA.z / f;
		temp.w = vecA.w / f;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fDiv(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		temp.x = vecA.x / vecB.x;
		temp.y = vecA.y / vecB.y;
		temp.z = vecA.z / vecB.z;
		temp.w = vecA.w / vecB.w;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fMin(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		temp.x = min(vecA.x, vecB.x);
		temp.y = min(vecA.y, vecB.y);
		temp.z = min(vecA.z, vecB.z);
		temp.w = min(vecA.w, vecB.w);
		return temp;
	}

	_NINLINE NMVector4f NMVector4fMax(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		temp.x = max(vecA.x, vecB.x);
		temp.y = max(vecA.y, vecB.y);
		temp.z = max(vecA.z, vecB.z);
		temp.w = max(vecA.w, vecB.w);
		return temp;
	}

	_NINLINE NMVector4f NMVector4fAbs(const NMVector4f& vec)
	{
		return NMVector4fMax(vec, NMVector4fNeg(vec));
	}

	_NINLINE NMVector4f NMVector4fNeg(const NMVector4f& vec)
	{
		return NMVector4fSub(NMVector4fLoadZeros(), vec);
	}

	_NINLINE NMVector4f NMVector4fAnd(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		((NUint32*)&temp.x)[0] = ((NUint32*)&vecA.x)[0] & ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ((NUint32*)&vecA.y)[0] & ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ((NUint32*)&vecA.z)[0] & ((NUint32*)&vecB.z)[0];
		((NUint32*)&temp.w)[0] = ((NUint32*)&vecA.w)[0] & ((NUint32*)&vecB.w)[0];
		return temp;
	}

	_NINLINE NMVector4f NMVector4fAndNot(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		((NUint32*)&temp.x)[0] = ~((NUint32*)&vecA.x)[0] & ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ~((NUint32*)&vecA.y)[0] & ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ~((NUint32*)&vecA.z)[0] & ((NUint32*)&vecB.z)[0];
		((NUint32*)&temp.w)[0] = ~((NUint32*)&vecA.w)[0] & ((NUint32*)&vecB.w)[0];
		return temp;
	}

	_NINLINE NMVector4f NMVector4fOr(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		((NUint32*)&temp.x)[0] = ((NUint32*)&vecA.x)[0] | ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ((NUint32*)&vecA.y)[0] | ((NUint32*)&vecB.y)[0];
		((NUint32*)&temp.z)[0] = ((NUint32*)&vecA.z)[0] | ((NUint32*)&vecB.z)[0];
		((NUint32*)&temp.w)[0] = ((NUint32*)&vecA.w)[0] | ((NUint32*)&vecB.w)[0];
		return temp;
	}

	_NINLINE NMVector4f NMVector4fNot(const NMVector4f& vec)
	{
		NMVector4f temp;
		((NUint32*)&temp.x)[0] = ~((NUint32*)&vec.x)[0];
		((NUint32*)&temp.y)[0] = ~((NUint32*)&vec.y)[0];
		((NUint32*)&temp.z)[0] = ~((NUint32*)&vec.z)[0];
		((NUint32*)&temp.w)[0] = ~((NUint32*)&vec.w)[0];
		return temp;
	}

	_NINLINE NMVector4f NMVector4fGreater(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		((NUint32*)&temp.x)[0] = vecA.x > vecB.x ? 0xffffffff : 0x0;
		((NUint32*)&temp.y)[0] = vecA.y > vecB.y ? 0xffffffff : 0x0;
		((NUint32*)&temp.z)[0] = vecA.z > vecB.z ? 0xffffffff : 0x0;
		((NUint32*)&temp.w)[0] = vecA.w > vecB.w ? 0xffffffff : 0x0;
		return temp;
	}

	_NINLINE NMVector4f NMVector4fLess(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		NMVector4f temp;
		((NUint32*)&temp.x)[0] = vecA.x < vecB.x ? 0xffffffff : 0x0;
		((NUint32*)&temp.y)[0] = vecA.y < vecB.y ? 0xffffffff : 0x0;
		((NUint32*)&temp.z)[0] = vecA.z < vecB.z ? 0xffffffff : 0x0;
		((NUint32*)&temp.w)[0] = vecA.w < vecB.w ? 0xffffffff : 0x0;
		return temp;
	}

	_NINLINE NMVector4f operator+(const NMVector4f& vec)
	{
		return vec;
	}

	_NINLINE NMVector4f operator-(const NMVector4f& vec)
	{
		return NMVector4fNeg(vec);
	}

	_NINLINE NMVector4f operator+(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		return NMVector4fAdd(vecA, vecB);
	}

	_NINLINE NMVector4f operator-(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		return NMVector4fSub(vecA, vecB);
	}

	_NINLINE NMVector4f operator*(const NMVector4f& vecA, float f)
	{
		return NMVector4fMul(vecA, f);
	}

	_NINLINE NMVector4f operator*(float f, const NMVector4f& vecA)
	{
		return NMVector4fMul(vecA, f);
	}

	_NINLINE NMVector4f operator*(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		return NMVector4fMul(vecA, vecB);
	}

	_NINLINE NMVector4f operator/(const NMVector4f& vecA, float f)
	{
		return NMVector4fDiv(vecA, f);
	}

	_NINLINE NMVector4f operator/(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		return NMVector4fDiv(vecA, vecB);
	}

	_NINLINE NMVector4f operator&(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		return NMVector4fAnd(vecA, vecB);
	}

	_NINLINE NMVector4f operator|(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		return NMVector4fOr(vecA, vecB);
	}

	_NINLINE NMVector4f operator~(const NMVector4f& vec)
	{
		return NMVector4fNot(vec);
	}

	_NINLINE NMVector4f operator>(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		return NMVector4fGreater(vecA, vecB);
	}

	_NINLINE NMVector4f operator<(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		return NMVector4fLess(vecA, vecB);
	}
	
	_NINLINE NMVector4f& operator+=(NMVector4f& vecA, const NMVector4f& vecB)
	{
		vecA.x += vecB.x;
		vecA.y += vecB.y;
		vecA.z += vecB.z;
		vecA.w += vecB.w;
		return vecA;
	}

	_NINLINE NMVector4f& operator-=(NMVector4f& vecA, const NMVector4f& vecB)
	{
		vecA.x -= vecB.x;
		vecA.y -= vecB.y;
		vecA.z -= vecB.z;
		vecA.w -= vecB.w;
		return vecA;
	}

	_NINLINE NMVector4f& operator*=(NMVector4f& vecA, float f)
	{
		vecA.x *= f;
		vecA.y *= f;
		vecA.z *= f;
		vecA.w *= f;
		return vecA;
	}

	_NINLINE NMVector4f& operator*=(NMVector4f& vecA, const NMVector4f& vecB)
	{
		vecA.x *= vecB.x;
		vecA.y *= vecB.y;
		vecA.z *= vecB.z;
		vecA.w *= vecB.w;
		return vecA;
	}

	_NINLINE NMVector4f& operator/=(NMVector4f& vecA, float f)
	{
		vecA.x /= f;
		vecA.y /= f;
		vecA.z /= f;
		vecA.w /= f;
		return vecA;
	}

	_NINLINE NMVector4f& operator/=(NMVector4f& vecA, const NMVector4f& vecB)
	{
		vecA.x /= vecB.x;
		vecA.y /= vecB.y;
		vecA.z /= vecB.z;
		vecA.w /= vecB.w;
		return vecA;
	}

	_NINLINE float NMVector4fDot(const NMVector4f& vecA, const NMVector4f& vecB)
	{
		float f;
		f = vecA.x * vecB.x;
		f += vecA.y * vecB.y;
		f += vecA.z * vecB.z;
		f += vecA.w * vecB.w;
		return f;
	}

	_NINLINE float NMVector4fLength(const NMVector4f& vec)
	{
		return sqrt(NMVector4fDot(vec, vec));
	}

	_NINLINE NMVector4f NMVector4fNormalize(const NMVector4f& vec)
	{
		return NMVector4fDiv(vec, NMVector4fLength(vec));
	}
}