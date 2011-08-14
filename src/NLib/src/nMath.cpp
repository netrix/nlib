#include "../nMath.hpp"

namespace NIne
{
	/****************************************************/
	// NMUtilities
	float NMTurbulence(float x, float y, float fWidth, float fHeight)
	{
		int iOctaves = 4;
		float fPersistence = 0.5f; // Persistence [0-1]. 1=All octaves added equally.
		float fResult = 0;
		NUint32 uFrequency = 1; // Can't see amplitudes less than 1/256.
		for(float fAmplitude = 1; (iOctaves--) && (fAmplitude > 1.0f / 256.0f); fAmplitude *= fPersistence, uFrequency <<= 1) 
		{
			fResult += fAmplitude * fabs(NMInterpolatedNoise(fWidth * (fHeight * y + x) * uFrequency));
		}
		fResult = (fResult + 1) / 2.0f;

		return fResult;
	}
	/****************************************************/
	float NMSmoothNoise(float x, float y, NUint32 uNoiseWidth, NUint32 uNoiseHeight)
	{  
	   float fractX = x - int(x);	// Fract part
	   float fractY = y - int(y);
	   
	   NUint32 x1 = (NUint32(x) + uNoiseWidth) % uNoiseWidth;	// Wrapping around and neighbours
	   NUint32 y1 = (NUint32(y) + uNoiseHeight) % uNoiseHeight;
	   NUint32 x2 = (x1 + uNoiseWidth - 1) % uNoiseWidth;
	   NUint32 y2 = (y1 + uNoiseHeight - 1) % uNoiseHeight;

	   float value = 0.0;
	   value += fractX       * fractY       * NMNoiseNormalized(x1, y1);
	   value += fractX       * (1 - fractY) * NMNoiseNormalized(x1, y2);
	   value += (1 - fractX) * fractY       * NMNoiseNormalized(x2, y1);
	   value += (1 - fractX) * (1 - fractY) * NMNoiseNormalized(x2, y2);

	   return value;
	}
	/****************************************************/
	float NMCloud(float x,float y, float size, float minSize)
	{
		float value = 0.0f, initialSize = size; 

		while(size >= minSize)
		{
			value += NMSmoothNoise(x / size, y / size, 100, 100) * size;	// 100 -> 128
			size /= 2.0f;
		}    
		return(value / initialSize);
	}
}