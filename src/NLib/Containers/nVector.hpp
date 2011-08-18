#pragma once
#include "../Memory/nArray.hpp"

namespace NLib {
namespace Containers
{
	// Help function
	template<typename TYPE>
	void NSwap(TYPE& srcA, TYPE& srcB)
	{
		TYPE temp = srcA;
		srcA = srcB;
		srcB = srcA;
	}

	template<typename Type, unsigned ALIGN_SIZE = 0, Memory::NMemory& memory = Memory::NMemoryGlobal>
	class NVector
	{
	public:
		NVector()	: m_uReallocSize(0), m_uSize(0)		{ }

		void		create(NSize_t uSize, NSize_t uReallocSize = 4);
		void		create(const NVector<Type, ALIGN_SIZE, memory>& src);

		void		reserve(NSize_t uSize);
		void		resize(NSize_t uSize);

		void		setReallocSize(NSize_t uReallocSize);

		void		clear()				{ m_uSize = 0; }
		void		release();

		void		push_back(const Type& element);
		void		pop_back();

		void		insert(NSize_t uIndex, const Type& element);

		void		remove(NSize_t uIndex);
		void		removeUnordered(NSize_t uIndex);

		NSize_t		find(const Type& element);

		NSize_t		size() const		{ return m_uSize; }
		NSize_t		capacity() const	{ return m_array.size(); }
		bool		empty() const		{ return m_uSize == 0; }

		const Type* data() const		{ return m_array.data(); }
		Type*		data()				{ return m_array.data(); }

		const Type& operator[](NSize_t uIndex) const;
		Type&		operator[](NSize_t uIndex);

		operator bool() const			{ return m_array; }

	public:
		static Memory::NMemory&		getMemory()		{ return memory; }

	private:
		Memory::NArray<Type, ALIGN_SIZE, memory> m_array;

		NSize_t m_uSize;
		NSize_t m_uReallocSize;
	};

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::create(NSize_t uSize, NSize_t uReallocSize)
	{
		m_array.create(uSize);
		m_uReallocSize = uReallocSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::create(const NVector<Type, ALIGN_SIZE, memory>& src)
	{
		m_array.create(src.m_array);

		m_uReallocSize = src.m_uReallocSize;
		m_uSize = src.m_uSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::setReallocSize(NSize_t uReallocSize)
	{
		NAssert(uReallocSize > 0, "uReallocSize must be > 0");
		m_uReallocSize = uReallocSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::release()
	{
		m_array.release();
		m_uSize = 0;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::push_back(const Type& element)
	{
		if(m_uSize + 1 > m_array.size())	{ m_array.resize(m_array.size() + m_uReallocSize); }

		m_array[m_uSize] = element;
		++m_uSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::pop_back()
	{
		NAssert(m_uSize > 0, "NVector is empty!");
		--m_uSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::insert(NSize_t uIndex, const Type& element)
	{
		NAssert(uIndex < m_uSize, "uIndex must be < m_uSize");

		if(m_uSize + 1 > m_array.size())	{ m_array.resize(m_array.size() + m_uReallocSize); }

		memcpy(m_array.data() + uIndex + 1, m_array.data() + uIndex, sizeof(Type) * (m_uSize - uIndex - 1));
		m_array[uIndex] = element;
		++m_uSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::remove(NSize_t uIndex)
	{
		NAssert(uIndex < m_uSize, "uIndex must be < m_uSize");

		if(uIndex < m_uSize - 1)	{ memcpy(m_array.data() + uIndex, m_array.data() + uIndex + 1, sizeof(Type) * (m_uSize - uIndex - 1)); }
		--m_uSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::removeUnordered(NSize_t uIndex)
	{
		NAssert(uIndex < m_uSize, "uIndex must be < m_uSize");

		if(uIndex < m_uSize - 1) { m_array[uIndex] = m_array[m_uSize - 1]; }
		--m_uSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	NSize_t NVector<Type, ALIGN_SIZE, memory>::find(const Type& element)
	{
		NSize_t uIndex = 0;
		while(uIndex < m_uSize && m_array[uIndex] != element)	{ ++uIndex;	}
		return uIndex;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	const Type& NVector<Type, ALIGN_SIZE, memory>::operator[](NSize_t uIndex) const
	{
		NAssert(uIndex < m_uSize, "Index out of bounds");
		return m_array[uIndex];
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	Type& NVector<Type, ALIGN_SIZE, memory>::operator[](NSize_t uIndex)
	{
		NAssert(uIndex < m_uSize, "Index out of bounds");
		return m_array[uIndex];
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::reserve(NSize_t uSize)
	{
		if(uSize > m_array.size())	{ m_array.resize(uSize); }
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NVector<Type, ALIGN_SIZE, memory>::resize(NSize_t uSize)
	{
		if(uSize > m_array.size())	{ m_array.resize(uSize); }
		m_uSize = uSize;
	}
}
}