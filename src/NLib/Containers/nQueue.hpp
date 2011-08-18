#pragma once
#include "../Memory/nArray.hpp"

namespace NLib {
namespace Containers
{
	template<typename Type, Memory::NMemory& memory = Memory::NMemoryGlobal>
	class NQueue
	{
	public:
		NQueue()	: m_uReallocSize(0), m_uSize(0), m_uActualBack(0), m_uActualFront(0)	{ }

		void		create(NSize_t uSize, NSize_t uReallocSize = 10);
		void		create(const NQueue<Type>& src);

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
		NSize_t		size() const		{ return m_uSize; }

		void		reserve(NSize_t uSize);

		operator bool() const			{ return m_data; }

	public:
		static Memory::NMemory&		getMemory()		{ return memory; }

	private:
		NArray<Type, memory> m_data;
		NSize_t m_uSize;
		NSize_t m_uReallocSize;

		NSize_t m_uActualFront;	// Actual front of the queue
		NSize_t m_uActualBack;  // Actual back - can be m_uActualFront + m_uSize, but then need to be checked
	};

	template<typename Type, Memory::NMemory& memory>
	void NQueue<Type, memory>::create(NSize_t uSize, NSize_t uReallocSize)
	{
		m_data.create(uSize);
		m_uReallocSize = uReallocSize;
	}

	template<typename Type, Memory::NMemory& memory>
	void NQueue<Type, memory>::create(const NQueue<Type, memory>& src)
	{
		m_data.create(src.m_data);

		m_uReallocSize = src.m_uReallocSize;
		m_uSize = src.m_uSize;
		m_uActualFront = src.m_uActualFront;
		m_uActualBack = src.m_uActualBack;
	}

	template<typename Type, Memory::NMemory& memory>
	void NQueue<Type, memory>::setReallocSize(NSize_t uReallocSize)
	{
		NAssert(uReallocSize > 0, "uReallocSize must be > 0");

		m_uReallocSize = uReallocSize;
	}

	template<typename Type, Memory::NMemory& memory>
	void NQueue<Type, memory>::clear()
	{
		m_uSize = 0;
		m_uActualFront = 0;
		m_uActualBack = 0;
	}

	template<typename Type, Memory::NMemory& memory>
	void NQueue<Type, memory>::release()
	{
		m_data.release();
		Clear();
	}

	template<typename Type, Memory::NMemory& memory>
	void NQueue<Type, memory>::push_back(const Type& element)
	{
		if(m_uSize + 1 > m_data.size())	// Full
		{
			if(m_uActualBack != (m_data.size() - 1))	// In the middle
			{
				Memory::NArray<Type, memory> temp;
				temp.create(m_data.size() + m_uReallocSize);
				memcpy(temp.data(), m_data.data() + m_uActualFront, m_data.size() - m_uActualFront);	// Copy front part
				memcpy(temp.data() + m_data.size() - m_uActualFront, m_data.data(), m_uActualFront);	// Copy back part
				m_uActualFront = 0;
				m_data.release();
				m_data = temp;
			}
			else	{ m_data.resize(m_data.size() + m_uReallocSize); }
		}

		++m_uSize;
		m_uActualBack = m_uActualFront + m_uSize > m_data.size() ? m_uSize -  (m_data.size() - m_uActualFront) - 1 : m_uActualFront + m_uSize - 1;
		m_data[m_uActualBack] = element;
	}

	template<typename Type, Memory::NMemory& memory>
	void NQueue<Type, memory>::pop_front()
	{
		if(++m_uActualFront == m_data.size())	{ m_uActualFront = 0; }
		m_uSize = m_uSize > 0 ? m_uSize - 1 : 0;
	}

	template<typename Type, Memory::NMemory& memory>
	void NQueue<Type, memory>::reserve(NSize_t uSize)
	{
		if(uSize > m_data.size())	// Full
		{
			if(m_uActualBack < m_uActualFront)	// In the middle
			{
				NDynamicTable<Type> temp;
				temp.Create(m_data.size() + m_uReallocSize);
				memcpy(temp.data(), m_data.data() + m_uActualFront, m_data.size() - m_uActualFront);	// Copy front part
				memcpy(temp.data() + m_data.size() - m_uActualFront, m_data.data(), m_uActualFront);	// Copy back part
				m_uActualFront = 0;
				m_uActualBack = m_uSize - 1;
				m_data.release();
				m_data = temp;
			}
			else	{ m_data.Resize(m_data.size() + m_uReallocSize); }
		}
	}
}
}