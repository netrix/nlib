#pragma once
// Included in nMath.hpp

namespace NIne
{
	/****************************************************/
	// Declarations
	_NINLINE NMVector2f NMVector2fLoad(const float* pFloats);
	_NINLINE NMVector2f NMVector2fLoad(float f);
	_NINLINE NMVector2f NMVector2fLoad(float x, float y);

	_NINLINE NMVector2f NMVector2fLoadZeros();

	_NINLINE NMVector2f NMVector2fAdd(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fSub(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fMul(const NMVector2f& vecA, float f);
	_NINLINE NMVector2f NMVector2fMul(float f, const NMVector2f& vecA);
	_NINLINE NMVector2f NMVector2fMul(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fDiv(const NMVector2f& vecA, float f);
	_NINLINE NMVector2f NMVector2fDiv(const NMVector2f& vecA, const NMVector2f& vecB);

	_NINLINE NMVector2f NMVector2fMin(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fMax(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fAbs(const NMVector2f& vec);
	_NINLINE NMVector2f NMVector2fNeg(const NMVector2f& vec);

	_NINLINE NMVector2f NMVector2fAnd(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fAndNot(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fOr(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fNot(const NMVector2f& vecv);

	_NINLINE NMVector2f NMVector2fGreater(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fLess(const NMVector2f& vecA, const NMVector2f& vecB);

	_NINLINE NMVector2f operator+(const NMVector2f& vec);
	_NINLINE NMVector2f operator-(const NMVector2f& vec);
	_NINLINE NMVector2f operator+(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f operator-(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f operator*(const NMVector2f& vecA, float f);
	_NINLINE NMVector2f operator*(float f, const NMVector2f& vecA);
	_NINLINE NMVector2f operator*(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f operator/(const NMVector2f& vecA, float f);
	_NINLINE NMVector2f operator/(const NMVector2f& vecA, const NMVector2f& vecB);
	
	_NINLINE NMVector2f& operator+=(NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f& operator-=(NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f& operator*=(NMVector2f& vecA, float f);
	_NINLINE NMVector2f& operator/=(NMVector2f& vecA, float f);

	_NINLINE NMVector2f operator&(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f operator|(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f operator~(const NMVector2f& vec);

	_NINLINE NMVector2f operator>(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f operator<(const NMVector2f& vecA, const NMVector2f& vecB);

	_NINLINE float NMVector2fLength(const NMVector2f& vec);
	_NINLINE float NMVector2fDot(const NMVector2f& vecA, const NMVector2f& vecB);
	_NINLINE NMVector2f NMVector2fNormalize(const NMVector2f& vec);

	/****************************************************/
	// Definitions
	_NINLINE NMVector2f NMVector2fLoad(const float* pFloats)
	{
		NMVector2f temp;
		((NUint32*)&temp.x)[0] = ((const NUint32*)(&pFloats[0]))[0];
		((NUint32*)&temp.y)[0] = ((const NUint32*)(&pFloats[1]))[0];
		return temp;
	}

	_NINLINE NMVector2f NMVector2fLoad(float f)
	{
		NMVector2f temp;
		temp.x = f;
		temp.y = f;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fLoad(float x, float y)
	{
		NMVector2f temp;
		temp.x = x;
		temp.y = y;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fLoadZeros()
	{
		NMVector2f temp;
		((NUint32*)&temp.x)[0] = 0;
		((NUint32*)&temp.y)[0] = 0;
		return temp;
	}

	_NINLINE void NMVector2fStore(float* pFloats, const NMVector2f& vec)
	{
		((NUint32*)&pFloats[0])[0] = ((const NUint32*)(&vec.x))[0];
		((NUint32*)&pFloats[1])[0] = ((const NUint32*)(&vec.y))[0];
	}

	_NINLINE NMVector2f NMVector2fAdd(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		temp.x = vecA.x + vecB.x;
		temp.y = vecA.y + vecB.y;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fSub(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		temp.x = vecA.x - vecB.x;
		temp.y = vecA.y - vecB.y;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fMul(const NMVector2f& vecA, float f)
	{
		NMVector2f temp;
		temp.x = vecA.x * f;
		temp.y = vecA.y * f;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fMul(float f, const NMVector2f& vecA)
	{
		return NMVector2fMul(vecA, f);
	}

	_NINLINE NMVector2f NMVector2fMul(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		temp.x = vecA.x * vecB.x;
		temp.y = vecA.y * vecB.y;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fDiv(const NMVector2f& vecA, float f)
	{
		NMVector2f temp;
		temp.x = vecA.x / f;
		temp.y = vecA.y / f;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fDiv(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		temp.x = vecA.x / vecB.x;
		temp.y = vecA.y / vecB.y;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fMin(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		temp.x = min(vecA.x, vecB.x);
		temp.y = min(vecA.y, vecB.y);
		return temp;
	}

	_NINLINE NMVector2f NMVector2fMax(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		temp.x = max(vecA.x, vecB.x);
		temp.y = max(vecA.y, vecB.y);
		return temp;
	}

	_NINLINE NMVector2f NMVector2fAbs(const NMVector2f& vec)
	{
		return NMVector2fMax(vec, NMVector2fNeg(vec));
	}

	_NINLINE NMVector2f NMVector2fNeg(const NMVector2f& vec)
	{
		return NMVector2fSub(NMVector2fLoadZeros(), vec);
	}

	_NINLINE NMVector2f NMVector2fAnd(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		((NUint32*)&temp.x)[0] = ((NUint32*)&vecA.x)[0] & ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ((NUint32*)&vecA.y)[0] & ((NUint32*)&vecB.y)[0];
		return temp;
	}

	_NINLINE NMVector2f NMVector2fAndNot(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		((NUint32*)&temp.x)[0] = ~((NUint32*)&vecA.x)[0] & ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ~((NUint32*)&vecA.y)[0] & ((NUint32*)&vecB.y)[0];
		return temp;
	}

	_NINLINE NMVector2f NMVector2fOr(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		((NUint32*)&temp.x)[0] = ((NUint32*)&vecA.x)[0] | ((NUint32*)&vecB.x)[0];
		((NUint32*)&temp.y)[0] = ((NUint32*)&vecA.y)[0] | ((NUint32*)&vecB.y)[0];
		return temp;
	}

	_NINLINE NMVector2f NMVector2fNot(const NMVector2f& vec)
	{
		NMVector2f temp;
		((NUint32*)&temp.x)[0] = ~((NUint32*)&vec.x)[0];
		((NUint32*)&temp.y)[0] = ~((NUint32*)&vec.y)[0];
		return temp;
	}

	_NINLINE NMVector2f NMVector2fGreater(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		((NUint32*)&temp.x)[0] = vecA.x > vecB.x ? 0xffffffff : 0x0;
		((NUint32*)&temp.y)[0] = vecA.y > vecB.y ? 0xffffffff : 0x0;
		return temp;
	}

	_NINLINE NMVector2f NMVector2fLess(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		NMVector2f temp;
		((NUint32*)&temp.x)[0] = vecA.x < vecB.x ? 0xffffffff : 0x0;
		((NUint32*)&temp.y)[0] = vecA.y < vecB.y ? 0xffffffff : 0x0;
		return temp;
	}

	_NINLINE NMVector2f operator+(const NMVector2f& vec)
	{
		return vec;
	}

	_NINLINE NMVector2f operator-(const NMVector2f& vec)
	{
		return NMVector2fNeg(vec);
	}

	_NINLINE NMVector2f operator+(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		return NMVector2fAdd(vecA, vecB);
	}

	_NINLINE NMVector2f operator-(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		return NMVector2fSub(vecA, vecB);
	}

	_NINLINE NMVector2f operator*(const NMVector2f& vecA, float f)
	{
		return NMVector2fMul(vecA, f);
	}

	_NINLINE NMVector2f operator*(float f, const NMVector2f& vecA)
	{
		return NMVector2fMul(vecA, f);
	}

	_NINLINE NMVector2f operator*(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		return NMVector2fMul(vecA, vecB);
	}

	_NINLINE NMVector2f operator/(const NMVector2f& vecA, float f)
	{
		return NMVector2fDiv(vecA, f);
	}

	_NINLINE NMVector2f operator/(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		return NMVector2fDiv(vecA, vecB);
	}

	_NINLINE NMVector2f operator&(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		return NMVector2fAnd(vecA, vecB);
	}

	_NINLINE NMVector2f operator|(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		return NMVector2fOr(vecA, vecB);
	}

	_NINLINE NMVector2f operator~(const NMVector2f& vec)
	{
		return NMVector2fNot(vec);
	}

	_NINLINE NMVector2f operator>(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		return NMVector2fGreater(vecA, vecB);
	}

	_NINLINE NMVector2f operator<(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		return NMVector2fLess(vecA, vecB);
	}
	
	_NINLINE NMVector2f& operator+=(NMVector2f& vecA, const NMVector2f& vecB)
	{
		vecA.x += vecB.x;
		vecA.y += vecB.y;
		return vecA;
	}

	_NINLINE NMVector2f& operator-=(NMVector2f& vecA, const NMVector2f& vecB)
	{
		vecA.x -= vecB.x;
		vecA.y -= vecB.y;
		return vecA;
	}

	_NINLINE NMVector2f& operator*=(NMVector2f& vecA, float f)
	{
		vecA.x *= f;
		vecA.y *= f;
		return vecA;
	}

	_NINLINE NMVector2f& operator*=(NMVector2f& vecA, const NMVector2f& vecB)
	{
		vecA.x *= vecB.x;
		vecA.y *= vecB.y;
		return vecA;
	}

	_NINLINE NMVector2f& operator/=(NMVector2f& vecA, float f)
	{
		vecA.x /= f;
		vecA.y /= f;
		return vecA;
	}

	_NINLINE NMVector2f& operator/=(NMVector2f& vecA, const NMVector2f& vecB)
	{
		vecA.x /= vecB.x;
		vecA.y /= vecB.y;
		return vecA;
	}

	_NINLINE float NMVector2fDot(const NMVector2f& vecA, const NMVector2f& vecB)
	{
		float f;
		f = vecA.x * vecB.x;
		f += vecA.y * vecB.y;
		return f;
	}

	_NINLINE float NMVector2fLength(const NMVector2f& vec)
	{
		return sqrt(NMVector2fDot(vec, vec));
	}

	_NINLINE NMVector2f NMVector2fNormalize(const NMVector2f& vec)
	{
		return NMVector2fDiv(vec, NMVector2fLength(vec));
	}
}