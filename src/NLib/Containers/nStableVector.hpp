#pragma once
#include "nVector.hpp"

namespace NLib {
namespace Containers
{
	template<typename Type, unsigned ALIGN_SIZE = 0, Memory::NMemory& memory = Memory::NMemoryGlobal>
	class NStableVector
	{
	public:
		void		create(NSize_t uSize, NSize_t uReallocSize = 4);
		void		create(const NStableVector<Type>& src);

		void		setReallocSize(NSize_t uReallocSize);
		void		reserve(NSize_t uSize);

		void		clear();
		void		release();

		void		insert(const Type& element, NSize_t& uNewIndex);
		void		remove(NSize_t uIndex);

		NSize_t		size() const						{ return m_data.GetSize() - m_freeIndices.GetSize(); }
		NSize_t		capacity() const					{ return m_data.capacity();	}
		bool		empty() const						{ return m_data.empty(); }

		const Type* data() const						{ return m_data.data();	}
		Type*		data()								{ return m_data.data();	}

		const Type& operator[](NSize_t uIndex) const	{ return m_data[uIndex]; }
		Type&		operator[](NSize_t uIndex)			{ return m_data[uIndex]; }

		operator bool() const							{ return m_data && m_freeIndices; }

	private:
		NVector<Type>	 m_data;
		NVector<NSize_t> m_freeIndices;
	};

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::create(NSize_t uSize, NSize_t uReallocSize)
	{
		m_data.create(uSize, uReallocSize);
		m_freeIndices.create(uSize, uReallocSize);
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::create(const NStableVector<Type, ALIGN_SIZE, memory>& src)
	{
		m_data.create(uSize, uReallocSize);
		m_freeIndices.create(uSize, uReallocSize);
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::setReallocSize(NSize_t uReallocSize)
	{
		m_data.setReallocSize(uReallocSize);
		m_freeIndices.setReallocSize(uReallocSize);
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::clear()
	{
		m_data.clear();
		m_freeIndices.clear();
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::release()
	{
		m_data.release();
		m_freeIndices.rselease();
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::insert(const Type& element, NSize_t& uNewIndex)
	{
		if(m_freeIndices.empty())
		{
			NSize_t uLastCapacity = m_data.capacity();
			m_data.push_back(element);

			if(uLastCapacity < m_data.capacity())	{ m_freeIndices.reserve(m_data.capacity()); }

			uNewIndex = m_data.size() - 1;
		}
		else
		{
			uNewIndex = m_freeIndices[m_freeIndices.size() - 1];
			m_data[uNewIndex] = element;
			m_freeIndices.pop_back();
		}
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::remove(NSize_t uIndex)
	{
		NAssert(uIndex < m_data.size(), "uIndex must be < size");

		m_freeIndices.push_back(uIndex);
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::reserve(NSize_t uSize)
	{
		m_data.reserve(uSize);
		m_freeIndices.reserve(uSize);	// Checks are done in NVector
	}
}
}