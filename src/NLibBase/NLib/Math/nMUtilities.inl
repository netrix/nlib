#pragma once
// Included in nMath.hpp

namespace NLib {
namespace Math
{
	/****************************************************/
	// Declarations
	_NINLINE float NMNoiseNormalized(NUint32 x);
	_NINLINE float NMNoiseNormalized(NUint32 x, NUint32 y);
	_NINLINE float NMClamp(float x, float a, float b);
	_NINLINE float NMParametrize(float x, float a, float b);
	_NINLINE float NMHermiteCurve(float t);
	_NINLINE float NMHermiteStep(float t, float a, float b);
	_NINLINE float NMHermiteCurveDeriverative(float t);
	_NINLINE float NMHermiteStepDeriverative(float t, float a, float b);
	_NINLINE float NMSmoothNoise(NUint32 x);
	_NINLINE float NMInterpolate(float t, float a, float b);
	_NINLINE float NMInterpolatedNoise(float x);
	_NINLINE float NMInterpolateBSpline(float t, float a, float b, float c, float d);

	float NMTurbulence(float x, float y, float fWidth, float fHeight);
	float NMSmoothNoise(float x, float y, NUint32 uNoiseWidth, NUint32 uNoiseHeight);
	float NMCloud(float x,float y, float size, float minSize = 1.0f);

	/****************************************************/
	// Definitions
	_NINLINE float NMNoiseNormalized(NLib::NUint32 x)
	{
		x = (x << 13) ^ x;
		return ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / float(0x7FFFFFFF);
	}

	_NINLINE float NMNoiseNormalized(NUint32 x, NUint32 y)
	{
		x = (x << 13) ^ y;
		y = (y << 6) ^ x;
		return ((y * (x * (x + y) * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / float(0x7FFFFFFF);
	}

	_NINLINE float NMClamp(float x, float a, float b)
	{
		return x < a ? a : (x > b ? b : x);
	}

	_NINLINE float NMParametrize(float x, float a, float b)
	{
		return float(x - a) / (b - a);
	}

	_NINLINE float NMHermiteCurve(float t)
	{
		return t * t * (3 - 2 * t);
	}

	_NINLINE float NMHermiteStep(float t, float a, float b)
	{
		if(a == b || t < a) return 0;
		if(t > b) return 1;
		return NMHermiteCurve(NMParametrize(t, a, b));
	}

	_NINLINE float NMHermiteCurveDeriverative(float t)
	{
		return 6 * t * (1 - t);
	}

	_NINLINE float NMHermiteStepDeriverative(float t, float a, float b)
	{
		if(a == b || t < a || t > b) return 0;
		return NMHermiteCurveDeriverative(NMParametrize(t, a, b));
	}

	_NINLINE float NMSmoothNoise(NUint32 x)
	{
		return NMNoiseNormalized(x) / 2 + NMNoiseNormalized(x - 1) / 4 + NMNoiseNormalized(x + 1) / 4;
	}

	_NINLINE float NMInterpolate(float t, float a, float b)
	{
		return a + (b - a) * t;
	}

	_NINLINE float NMInterpolatedNoise(float x)
	{
		NLib::NUint32 X = (NLib::NUint32)(x);
		return NMInterpolate(x - X, NMSmoothNoise(X), NMSmoothNoise(X + 1));
	}

	_NINLINE float NMInterpolateBSpline(float t, float a, float b, float c, float d)
	{
		return 1.0f/6.0f*(t*(t*(t*(-a+3*b-3*c+d)+(3*a-6*b+3*c))+3*(c-a))+(a+4*b+c));
	}
}
}