#pragma once

#include "nVector.hpp"

namespace NIne
{
	template<typename Type>
	class NStableVector
	{
	public:
		NRESULT create(NSize_t uSize, NSize_t uReallocSize = 4)
		{
			NRESULT result;
			NRESULT_CP(result, m_buffer.create(uSize, uReallocSize));
			if(NFAILED(result = m_freeIndices.create(uSize, uReallocSize))
			{
				m_buffer.release();
				return result;
			}

			return NRV_SUCCESS;
		}

		NRESULT create(const NStableVector<Type>& src)
		{
			NRESULT result;
			NRESULT_CP(result, m_buffer.create(uSize, uReallocSize));
			if(NFAILED(result = m_freeIndices.create(uSize, uReallocSize))
			{
				m_buffer.release();
				return result;
			}

			return NRV_SUCCESS;
		}

		void setReallocSize(NSize_t uReallocSize)
		{
			m_buffer.setReallocSize(uReallocSize);
			m_freeIndices.setReallocSize(uReallocSize);
		}

		void Clear()
		{
			m_buffer.Clear();
			m_freeIndices.Clear();
		}

		void Release()
		{
			m_buffer.Release();
			m_freeIndices.Release();
		}

		NRESULT PushElement(const Type& element, NSize_t& uNewIndex)
		{
			NRESULT result;

			if(m_freeIndices.IsEmpty())
			{
				NSize_t uLastCapacity = m_buffer.GetCapacity();
				NRESULT_CP(result, m_buffer.PushElement(element));

				if(uLastCapacity < m_buffer.GetCapacity())
				{
					NRESULT_CP(result, m_freeIndices.Reserve(m_buffer.GetCapacity()));
				}

				uNewIndex = m_buffer.GetSize() - 1;
			}
			else
			{
				uNewIndex = m_freeIndices[m_freeIndices.GetSize() - 1];
				m_buffer[uNewIndex] = element;
				m_freeIndices.PopElement();
			}

			return NRV_SUCCESS;
		}

		void PopElement(NSize_t uIndex)
		{
			NAssert(uIndex < m_buffer.GetSize(), "uIndex must be < size");

			m_freeIndices.PushElement(uIndex);
		}

		const Type* GetBuffer() const
		{
			return m_buffer.GetBuffer();
		}

		Type* GetBuffer()
		{
			return m_buffer.GetBuffer();
		}

		const Type& operator[](NSize_t uIndex) const
		{
			NAssert(uIndex < m_buffer.GetSize(), "Index out of bounds");
			return m_buffer[uIndex];
		}

		Type& operator[](NSize_t uIndex)
		{
			NAssert(uIndex < m_buffer.GetSize(), "Index out of bounds");
			return m_buffer[uIndex];
		}

		NSize_t GetCapacity() const
		{
			return m_buffer.GetCapacity();
		}

		bool IsEmpty() const
		{
			return m_buffer.IsEmpty();
		}

		NSize_t GetSize() const
		{
			return m_buffer.GetSize() - m_freeIndices.GetSize();
		}

		NRESULT Reserve(NSize_t uSize)
		{
			NRESULT result;

			if(uSize > m_buffer.GetCapacity())
			{
				NRESULT_CP(result, m_buffer.Reserve(uSize));
				NRESULT_CP(result, m_freeIndices.Reserve(uSize));
			}

			return NRV_SUCCESS;
		}

		operator bool() const
		{
			return m_buffer && m_freeIndices;
		}

	private:
		NVector<Type> m_buffer;
		NVector<NSize_t> m_freeIndices;
	};
}