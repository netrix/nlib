#pragma once

#include "nContainerGuard.hpp"
#include <NLib/Base/nAssert.hpp>	// nBase.hpp
#include <NLib/Memory/nMemory.hpp>	// nBase.hpp, nErrors.hpp
#include <string.h>					// memcpy

namespace NLib {
namespace Containers
{
	template<typename Type, unsigned ALIGN_SIZE = 0, Memory::NMemory& memory = Memory::NMemoryGlobal>
	class NArray
	{
	public:
		NArray()	: m_pData(null), m_uSize(0)		{ }

		void		create(NSize_t uSize);
		void		create(const NArray<Type, ALIGN_SIZE, memory>& src);

		void		resize(NSize_t uSize);

		void		release();

		const Type* data() const		{ return m_pData; }
		Type*		data()				{ return m_pData; }

		NSize_t		size() const		{ return m_uSize; }

		const Type& operator[](NSize_t uIndex) const;
		Type&		operator[](NSize_t uIndex);

		operator bool() const			{	return m_pData != null; }

	public:
		static Memory::NMemory&		getMemory()		{ return memory; }

	private:
		Type*	m_pData;
		NSize_t m_uSize;
	};

#pragma warning(push)
#pragma warning(disable: 4127)

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NArray<Type, ALIGN_SIZE, memory>::create(NSize_t uSize)
	{
		NAssert(m_pData == null, "Buffer already allocated");
		NAssert(uSize > 0, "uSize is too small");

		// This is should be optimized by compiler
		if(ALIGN_SIZE == 0)		{ m_pData = (Type*)memory.allocate(uSize * sizeof(Type)); }
		else					{ m_pData = (Type*)memory.allocate(uSize * sizeof(Type), ALIGN_SIZE); }
		NCM_V(memory);

		m_uSize = uSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NArray<Type, ALIGN_SIZE, memory>::create(const NArray<Type, ALIGN_SIZE, memory>& src)
	{
		NAssert(m_pData == null, "Buffer already allocated");

		if(src.m_uSize > 0)
		{
			// This is should be optimized by compiler
			if(ALIGN_SIZE == 0)		{ m_pData = (Type*)memory.allocate(src.m_uSize * sizeof(Type)); }
			else					{ m_pData = (Type*)memory.allocate(src.m_uSize * sizeof(Type), ALIGN_SIZE); }
			NCM_V(memory);

			m_uSize = src.m_uSize;
			memcpy(m_pData, src.m_pData, m_uSize * sizeof(Type));
		}
		else	{ m_pData = null; }
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NArray<Type, ALIGN_SIZE, memory>::resize(NSize_t uSize)
	{
		NAssert(m_pData != null, "Buffer not allocated");
		NAssert(uSize > 0, "uSize is too small");

		if(uSize == m_uSize)	{ return; }

		// This is should be optimized by compiler
		Type* pData;
		if(ALIGN_SIZE == 0)		{ pData = (Type*)Memory::NMemoryAllocate(uSize * sizeof(Type)); }
		else					{ pData = (Type*)Memory::NMemoryAllocate(uSize * sizeof(Type), ALIGN_SIZE); }
		NCM_V(memory);

		memcpy(pData, m_pData, m_uSize * sizeof(Type));
		memory.release(m_pData);

		m_pData = pData;
		m_uSize = uSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NArray<Type, ALIGN_SIZE, memory>::release()
	{
		memory.release(m_pData);
		m_pData = null;
		m_uSize = 0;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	const Type& NArray<Type, ALIGN_SIZE, memory>::operator[](NSize_t uIndex) const
	{
		NAssert(uIndex < m_uSize, "Index out of bounds");

		return m_pData[uIndex];
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	Type& NArray<Type, ALIGN_SIZE, memory>::operator[](NSize_t uIndex)
	{
		NAssert(uIndex < m_uSize, "Index out of bounds");

		return m_pData[uIndex];
	}

#pragma warning(pop)
}
}
