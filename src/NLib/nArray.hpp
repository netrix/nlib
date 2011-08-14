#pragma once

#include "nBase.hpp"
#include "nAssert.hpp"
#include "nErrors.hpp"
#include <string.h>		// memcpy

namespace NIne
{
	template<typename Type, unsigned ALIGN_SIZE = 0>
	class NArray
	{
	public:
		NArray()	: m_pData(null), m_uSize(0)		{ }

		NRESULT		create(NSize_t uSize);
		NRESULT		create(const NArray<Type>& src);

		NRESULT		resize(NSize_t uSize);

		void		release();

		const Type* data() const		{ return m_pData; }
		Type*		data()				{ return m_pData; }

		NSize_t		size() const		{ return m_uSize; }

		const Type& operator[](NSize_t uIndex) const;
		Type&		operator[](NSize_t uIndex);

		operator bool() const			{	return m_pData != null; }

	private:
		Type*	m_pData;
		NSize_t m_uSize;
	};

	template<typename Type>
	NRESULT NArray<Type>::create(NSize_t uSize)
	{
		NAssert(m_pData == null, "Buffer already allocated");
		NAssert(uSize > 0, "uSize is too small");

		// This is should be optimized by compiler
		if(ALIGN_SIZE == 0)		{ m_pData = NNEW Type[uSize]; }
		else					{ NAlignedAlloc(&m_pData, uSize * sizeof(Type), ALIGN_SIZE); }

		if(m_pData == null)		{ return NRV_OUT_OF_MEMORY;	}

		m_uSize = uSize;
		return NRV_SUCCESS;
	}

	template<typename Type>
	NRESULT NArray<Type>::create(const NArray<Type>& src)
	{
		NAssert(m_pData == null, "Buffer already allocated");

		if(src.m_uSize > 0)
		{
			// This is should be optimized by compiler
			if(ALIGN_SIZE == 0)		{ m_pData = NNEW Type[src.m_uSize]; }
			else					{ NAlignedAlloc(&m_pData, src.m_uSize * sizeof(Type), ALIGN_SIZE); }

			if(m_pData == null)		{ return NRV_OUT_OF_MEMORY;	}

			m_uSize = src.m_uSize;
			memcpy(m_pData, src.m_pData, m_uSize * sizeof(Type));
		}
		else	{ m_pData = null; }

		return NRV_SUCCESS;
	}

	template<typename Type>
	NRESULT NArray<Type>::resize(NSize_t uSize)
	{
		NAssert(m_pData != null, "Buffer not allocated");
		NAssert(uSize > 0, "uSize is too small");

		if(uSize == m_uSize)	{ return NRV_SUCCESS; }

		// This is should be optimized by compiler
		if(ALIGN_SIZE == 0)		{ m_pData = NNEW Type[uSize]; }
		else					{ NAlignedAlloc(&m_pData, uSize * sizeof(Type), ALIGN_SIZE); }

		if(pBuffer == null)		{ return NRV_OUT_OF_MEMORY;	}

		memcpy(pBuffer, m_pData, m_uSize * sizeof(Type));
		delete [] m_pData;

		m_pData = pBuffer;
		m_uSize = uSize;
		return NRV_SUCCESS;
	}

	template<typename Type>
	void NArray<Type>::release()
	{
		if(ALIGN_SIZE == 0) { NDELETEARRNULL(m_pData); }
		else
		{
			if(m_pData != null)
			{
				NAlignedFree(m_pData);
				m_pData = null;
			}
		}

		m_uSize = 0;
	}

	template<typename Type>
	const Type& NArray<Type>::operator[](NSize_t uIndex) const
	{
		NAssert(uIndex < m_uSize, "Index out of bounds");

		return m_pData[uIndex];
	}

	template<typename Type>
	Type& NArray<Type>::operator[](NSize_t uIndex)
	{
		NAssert(uIndex < m_uSize, "Index out of bounds");

		return m_pData[uIndex];
	}

	// Help function
	template<typename TYPE>
	void NSwap(TYPE& srcA, TYPE& srcB)
	{
		TYPE temp = srcA;
		srcA = srcB;
		srcB = srcA;
	}
}