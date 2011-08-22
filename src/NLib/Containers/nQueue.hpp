#pragma once
#include "nContainerGuard.hpp"
#include "nArray.hpp"

namespace NLib {
namespace Containers
{
	template<typename Type, unsigned ALIGN_SIZE = 0, Memory::NMemory& memory = Memory::NMemoryGlobal>
	class NQueue
	{
	public:
		NQueue()	: m_uReallocSize(0), m_uSize(0), m_uActualBack(0), m_uActualFront(0)	{ }

		void		create(NSize_t uSize, NSize_t uReallocSize = 10);
		void		create(const NQueue& src);

		void		setReallocSize(NSize_t uReallocSize);

		void		clear();
		void		release();

		void		push_back(const Type& element);
		void		pop_front();

		Type*		front()				{ return m_uSize > 0 ? &m_data[m_uActualFront] : null; }
		const Type* front() const		{ return m_uSize > 0 ? &m_data[m_uActualFront] : null; }

		Type*		back()				{ return m_uSize > 0 ? &m_data[m_uActualBack] : null; }
		const Type* back() const		{ return m_uSize > 0 ? &m_data[m_uActualBack] : null; }

		NSize_t		capacity() const	{ return m_data.size();	}
		bool		empty() const		{ return m_uSize == 0; }
		bool		full() const		{ return m_uSize < m_data.size(); }
		NSize_t		size() const		{ return m_uSize; }

		void		reserve();
		void		reserve(NSize_t uSize);

		operator bool() const			{ return m_data; }

	public:
		static Memory::NMemory&		getMemory()		{ return memory; }

	private:
		Memory::NArray<Type, ALIGN_SIZE, memory> m_data;
		NSize_t m_uSize;
		NSize_t m_uReallocSize;

		NSize_t m_uActualFront;	// Actual front of the queue
		NSize_t m_uActualBack;  // Actual back - can be m_uActualFront + m_uSize, but then need to be checked
	};

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::create(NSize_t uSize, NSize_t uReallocSize)
	{
		m_data.create(uSize);			NCM_V(memory);
		m_uReallocSize = uReallocSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::create(const NQueue<Type, ALIGN_SIZE, memory>& src)
	{
		m_data.create(src.m_data);		NCM_V(memory);

		m_uReallocSize = src.m_uReallocSize;
		m_uSize = src.m_uSize;
		m_uActualFront = src.m_uActualFront;
		m_uActualBack = src.m_uActualBack;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::setReallocSize(NSize_t uReallocSize)
	{
		NAssert(uReallocSize > 0, "uReallocSize must be > 0");

		m_uReallocSize = uReallocSize;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::clear()
	{
		m_uSize = 0;
		m_uActualFront = 0;
		m_uActualBack = 0;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::release()
	{
		m_data.release();
		clear();
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::push_back(const Type& element)
	{
		if(m_uSize + 1 > m_data.size())	// Full
		{
			if(m_uActualBack != (m_data.size() - 1))	// In the middle
			{
				Memory::NArray<Type, memory> temp;
				temp.create(m_data.size() + m_uReallocSize);	NCM_V(memory);
				memcpy(temp.data(), m_data.data() + m_uActualFront, m_data.size() - m_uActualFront);	// Copy front part
				memcpy(temp.data() + m_data.size() - m_uActualFront, m_data.data(), m_uActualFront);	// Copy back part
				m_uActualFront = 0;
				m_data.release();
				m_data = temp;
			}
			else	{ m_data.resize(m_data.size() + m_uReallocSize); NCM_V(memory);}
		}

		++m_uSize;
		m_uActualBack = m_uActualFront + m_uSize > m_data.size() ? m_uSize -  (m_data.size() - m_uActualFront) - 1 : m_uActualFront + m_uSize - 1;
		m_data[m_uActualBack] = element;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::pop_front()
	{
		if(++m_uActualFront == m_data.size())	{ m_uActualFront = 0; }
		m_uSize = m_uSize > 0 ? m_uSize - 1 : 0;
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::reserve()
	{
		if(m_uActualBack < m_uActualFront)	// In the middle
		{
			NArray<Type> temp;
			temp.create(uSize);	NCM_V(memory);
			memcpy(temp.data(), m_data.data() + m_uActualFront, m_data.size() - m_uActualFront);	// Copy front part
			memcpy(temp.data() + m_data.size() - m_uActualFront, m_data.data(), m_uActualFront);	// Copy back part
			m_uActualFront = 0;
			m_uActualBack = m_uSize - 1;
			m_data.release();
			m_data = temp;
		}
		else	{ m_data.resize(m_data.size() + m_uReallocSize); }
	}

	template<typename Type, unsigned ALIGN_SIZE, Memory::NMemory& memory>
	void NQueue<Type, ALIGN_SIZE, memory>::reserve(NSize_t uSize)
	{
		if(uSize > m_data.size())	// Full
		{
			if(m_uActualBack < m_uActualFront)	// In the middle
			{
				NArray<Type> temp;
				temp.create(uSize);	NCM_V(memory);
				memcpy(temp.data(), m_data.data() + m_uActualFront, m_data.size() - m_uActualFront);	// Copy front part
				memcpy(temp.data() + m_data.size() - m_uActualFront, m_data.data(), m_uActualFront);	// Copy back part
				m_uActualFront = 0;
				m_uActualBack = m_uSize - 1;
				m_data.release();
				m_data = temp;
			}
			else	{ m_data.resize(m_data.size() + m_uReallocSize); }
		}
	}
}
}