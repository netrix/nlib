#pragma once
#include "nContainerGuard.hpp"
#include "nVector.hpp"

namespace NLib {
namespace Containers
{
	template<typename Type, unsigned ALIGN_SIZE = 0, Memory::NMemory& memory = Memory::NMemoryGlobal>
	class NStableVector
	{
	public:
		NStableVector()	: m_uSize(0), m_uFreeSize(0), m_uReallocSize(0) { }

		void		create(NSize_t uSize, NSize_t uReallocSize = 4);
		void		create(const NStableVector& src);

		void		setReallocSize(NSize_t uReallocSize);
		void		reserve();
		void		reserve(NSize_t uSize);

		void		clear();
		void		release();

		void		reserve(NSize_t* ouNewIndex);
		void		insert(const Type& element, NSize_t* ouNewIndex);
		void		remove(NSize_t uIndex);

		NSize_t		size() const						{ return m_uSize; }
		NSize_t		capacity() const					{ return m_data.size();	}
		bool		empty() const						{ return m_uSize == 0; }
		bool		full() const						{ return m_uSize == m_data.size(); }

		const Type* data() const						{ return m_data.data();	}
		Type*		data()								{ return m_data.data();	}

		const Type& operator[](NSize_t uIndex) const	{ return m_data[uIndex]; }
		Type&		operator[](NSize_t uIndex)			{ return m_data[uIndex]; }

		operator bool() const							{ return m_data && m_freeIndices; }

	public:
		static Memory::NMemory&		getMemory()		{ return memory; }

	private:
		NArray<Type>		m_data;
		NArray<NSize_t>		m_freeIndices;
		NSize_t		m_uSize;
		NSize_t		m_uFreeSize;
		NSize_t		m_uReallocSize;
	};

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::create(NSize_t uSize, NSize_t uReallocSize)
	{
		m_data.create(uSize);			NCM_V(memory);  NC_GUARD(NArray<Type>, m_data);
		m_freeIndices.create(uSize);	NCM_V(memory);  NC_GUARD_CLEAR(m_data);
		m_uReallocSize = uReallocSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::create(const NStableVector<Type, ALIGN_SIZE, memory>& src)
	{
		m_data.create(src.m_data);					NCM_V(memory);  NC_GUARD(NVector<Type>, m_data);
		m_freeIndices.create(src.m_freeIndices);	NCM_V(memory);  NC_GUARD_CLEAR(m_data);
		m_uFreeSize = src.m_uFreeSize;
		m_uSize = src.m_uSize;
		m_uReallocSize = src.m_uReallocSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::setReallocSize(NSize_t uReallocSize)
	{
		NAssert(uReallocSize > 0, "uReallocSize must be > 0");
		m_uReallocSize = uReallocSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::clear()
	{
		m_uSize = 0;
		m_uFreeSize = 0;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::release()
	{
		m_data.release();
		m_freeIndices.release();
		m_uSize = 0;
		m_uFreeSize = 0;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::reserve(NSize_t* ouNewIndex)
	{
		NAssert(ouNewIndex != null, "Invalid output pointer");

		if(m_uFreeSize == 0)
		{
			if(m_uSize == m_data.size())
			{
				m_freeIndices.resize(m_uSize + m_uReallocSize); NCM_V(memory);
				m_data.resize(m_uSize + m_uReallocSize);		NCM_V(memory);	// Order is important, because if 1st succeed and 2nd fails, container is still usable.
			}

			*ouNewIndex = m_uSize++;
		}
		else
		{
			*ouNewIndex = m_freeIndices[--m_uFreeSize];
		}
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::insert(const Type& element, NSize_t* ouNewIndex)
	{
		NAssert(ouNewIndex != null, "Invalid output pointer");

		reserve(ouNewIndex);	NCM_V(memory);
		m_data[*ouNewIndex] = element;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::remove(NSize_t uIndex)
	{
		NAssert(uIndex < m_data.size(), "uIndex must be < size");

		m_freeIndices[m_uFreeSize++] = uIndex;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::reserve()
	{
		m_freeIndices.resize(m_uSize + m_uReallocSize); NCM_V(memory);
		m_data.resize(m_uSize + m_uReallocSize);		NCM_V(memory);	// Order is important, because if 1st succeed and 2nd fails, container is still usable.
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NStableVector<Type, ALIGN_SIZE, memory>::reserve(NSize_t uSize)
	{
		m_freeIndices.resize(uSize);	NCM_V(memory);
		m_data.resize(uSize);			NCM_V(memory);	// Order is important, because if 1st succeed and 2nd fails, container is still usable.
	}
}
}