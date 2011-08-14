#pragma once

#include "nDynamicTable.hpp"

namespace NIne
{
	template<typename Type>
	class NDataQueue
	{
	public:
		NDataQueue()
			: m_uReallocSize(0),
			  m_uSize(0),
			  m_uActualBack(0),
			  m_uActualFront(0)
		{
		}

		NRESULT Create(NSize_t uSize, NSize_t uReallocSize = 10)
		{
			NRESULT result;
			NRESULT_CP(result, m_buffer.Create(uSize));

			m_uReallocSize = uReallocSize;

			return NRV_SUCCESS;
		}

		NRESULT Create(const NDataQueue<Type>& src)
		{
			NRESULT result;
			NRESULT_CP(result, m_buffer.Create(src.m_buffer));

			m_uReallocSize = src.m_uReallocSize;
			m_uSize = src.m_uSize;
			m_uActualFront = src.m_uActualFront;
			m_uActualBack = src.m_uActualBack;
			
			return NRV_SUCCESS;
		}

		void SetReallocSize(NSize_t uReallocSize)
		{
			NAssert(uReallocSize > 0, "uReallocSize must be > 0");

			m_uReallocSize = uReallocSize;
		}

		void Clear()
		{
			m_uSize = 0;
			m_uActualFront = 0;
			m_uActualBack = 0;
		}

		void Release()
		{
			m_buffer.Release();
			Clear();
		}

		NRESULT PushElement(const Type& element)
		{
			NRESULT result;

			if(m_uSize + 1 > m_buffer.GetSize())	// Full
			{
				if(m_uActualBack != (m_buffer.GetSize() - 1))	// In the middle
				{
					NDynamicTable<Type> temp;
					NRESULT_CP(result, temp.Create(m_buffer.GetSize() + m_uReallocSize));
					memcpy(temp.GetBuffer(), m_buffer.GetBuffer() + m_uActualFront, m_buffer.GetSize() - m_uActualFront);	// Copy front part
					memcpy(temp.GetBuffer() + m_buffer.GetSize() - m_uActualFront, m_buffer.GetBuffer(), m_uActualFront);	// Copy back part
					m_uActualFront = 0;
					m_buffer.Release();
					m_buffer = temp;
				}
				else
				{
					NRESULT_CP(result, m_buffer.Resize(m_buffer.GetSize() + m_uReallocSize));
				}
			}

			++m_uSize;
			m_uActualBack = m_uActualFront + m_uSize > m_buffer.GetSize() ? m_uSize -  (m_buffer.GetSize() - m_uActualFront) - 1 : m_uActualFront + m_uSize - 1;
			m_buffer[m_uActualBack] = element;

			return NRV_SUCCESS;
		}

		void PopElement()
		{
			if(++m_uActualFront == m_buffer.GetSize())
			{
				m_uActualFront = 0;
			}

			m_uSize = m_uSize > 0 ? m_uSize - 1 : 0;
		}

		Type* GetFront()
		{
			return m_uSize > 0 ? &m_buffer[m_uActualFront] : null;
		}

		const Type* GetFront() const
		{
			return m_uSize > 0 ? &m_buffer[m_uActualFront] : null;
		}

		Type* GetBack()
		{
			return m_uSize > 0 ? &m_buffer[m_uActualBack] : null;
		}

		const Type* GetBack() const
		{
			return m_uSize > 0 ? &m_buffer[m_uActualBack] : null;
		}

		NSize_t GetCapacity() const
		{
			return m_buffer.GetSize();
		}

		bool IsEmpty() const
		{
			return m_uSize == 0;
		}

		NSize_t GetSize() const
		{
			return m_uSize;
		}

		NRESULT Reserve(NSize_t uSize)
		{
			NRESULT result;

			if(uSize > m_buffer.GetSize())	// Full
			{
				if(m_uActualBack < m_uActualFront)	// In the middle
				{
					NDynamicTable<Type> temp;
					NRESULT_CP(result, temp.Create(m_buffer.GetSize() + m_uReallocSize));
					memcpy(temp.GetBuffer(), m_buffer.GetBuffer() + m_uActualFront, m_buffer.GetSize() - m_uActualFront);	// Copy front part
					memcpy(temp.GetBuffer() + m_buffer.GetSize() - m_uActualFront, m_buffer.GetBuffer(), m_uActualFront);	// Copy back part
					m_uActualFront = 0;
					m_uActualBack = m_uSize - 1;
					m_buffer.Release();
					m_buffer = temp;
				}
				else
				{
					NRESULT_CP(result, m_buffer.Resize(m_buffer.GetSize() + m_uReallocSize));
				}
			}

			return NRV_SUCCESS;
		}

		operator bool() const
		{
			return m_buffer;
		}

	private:
		NDynamicTable<Type> m_buffer;
		NSize_t m_uSize;
		NSize_t m_uReallocSize;

		NSize_t m_uActualFront;	// Actual front of the queue
		NSize_t m_uActualBack;  // Actual back - can be m_uActualFront + m_uSize, but then need to be checked
	};
}