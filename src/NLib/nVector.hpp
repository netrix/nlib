#pragma once
#include "nArray.hpp"

namespace NIne
{
	template<typename Type, unsigned ALIGN_SIZE = 0>
	class NVector
	{
	public:
		NVector()	: m_uReallocSize(0), m_uSize(0)		{ }

		NRESULT		create(NSize_t uSize, NSize_t uReallocSize = 4);
		NRESULT		create(const NVector<Type>& src);

		NRESULT		reserve(NSize_t uSize);
		NRESULT		resize(NSize_t uSize);

		void		setReallocSize(NSize_t uReallocSize);

		void		clear()				{ m_uSize = 0; }
		void		release();

		NRESULT		push_back(const Type& element);
		void		pop_back();

		NRESULT		insert(NSize_t uIndex, const Type& element);

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

	private:
		NDynamicTable<Type, ALIGN_SIZE> m_array;
		NSize_t m_uSize;
		NSize_t m_uReallocSize;
	};

	template<typename Type>
	NRESULT NVector<Type>::create(NSize_t uSize, NSize_t uReallocSize)
	{
		NRESULT result;
		NRESULT_CP(result, m_array.create(uSize));

		m_uReallocSize = uReallocSize;
		return NRV_SUCCESS;
	}

	template<typename Type>
	NRESULT NVector<Type>::create(const NVector<Type>& src)
	{
		NRESULT result;
		NRESULT_CP(result, m_array.create(src.m_array));

		m_uReallocSize = src.m_uReallocSize;
		m_uSize = src.m_uSize;

		return NRV_SUCCESS;
	}

	template<typename Type>
	void NVector<Type>::setReallocSize(NSize_t uReallocSize)
	{
		NAssert(uReallocSize > 0, "uReallocSize must be > 0");
		m_uReallocSize = uReallocSize;
	}

	template<typename Type>
	void NVector<Type>::release()
	{
		m_array.release();
		m_uSize = 0;
	}

	template<typename Type>
	NRESULT NVector<Type>::push_back(const Type& element)
	{
		if(m_uSize + 1 > m_array.size())
		{
			NRESULT result;
			NRESULT_CP(result, m_array.resize(m_array.size() + m_uReallocSize));
		}

		m_array[m_uSize] = element;
		++m_uSize;

		return NRV_SUCCESS;
	}

	template<typename Type>
	void NVector<Type>::pop_back()
	{
		NAssert(m_uSize > 0, "NVector is empty!");
		--m_uSize;
	}

	template<typename Type>
	NRESULT NVector<Type>::insert(NSize_t uIndex, const Type& element)
	{
		NAssert(uIndex < m_uSize, "uIndex must be < m_uSize");

		if(m_uSize + 1 > m_array.size())
		{
			NRESULT result;
			NRESULT_CP(result, m_array.resize(m_array.size() + m_uReallocSize));
		}

		memcpy(m_array.data() + uIndex + 1, m_array.data() + uIndex, sizeof(Type) * (m_uSize - uIndex - 1));
		m_array[uIndex] = element;

		++m_uSize;
		return NRV_SUCCESS;
	}

	template<typename Type>
	void NVector<Type>::remove(NSize_t uIndex)
	{
		NAssert(uIndex < m_uSize, "uIndex must be < m_uSize");

		if(uIndex < m_uSize - 1)
		{
			memcpy(m_array.data() + uIndex, m_array.data() + uIndex + 1, sizeof(Type) * (m_uSize - uIndex - 1));
		}
		--m_uSize;
	}

	template<typename Type>
	void NVector<Type>::removeUnordered(NSize_t uIndex)
	{
		NAssert(uIndex < m_uSize, "uIndex must be < m_uSize");

		if(uIndex < m_uSize - 1)
		{
			m_array[uIndex] = m_array[m_uSize - 1];
		}
		--m_uSize;
	}

	template<typename Type>
	NSize_t NVector<Type>::find(const Type& element)
	{
		NSize_t uIndex = 0;
		while(uIndex < m_uSize && m_array[uIndex] != element)
		{
			++uIndex;
		}
		return uIndex;
	}

	template<typename Type>
	const Type& NVector<Type>::operator[](NSize_t uIndex) const
	{
		NAssert(uIndex < m_uSize, "Index out of bounds");
		return m_array[uIndex];
	}

	template<typename Type>
	Type& NVector<Type>::operator[](NSize_t uIndex)
	{
		NAssert(uIndex < m_uSize, "Index out of bounds");
		return m_array[uIndex];
	}

	template<typename Type>
	NRESULT NVector<Type>::reserve(NSize_t uSize)
	{
		if(uSize > m_array.size())
		{
			NRESULT result;
			NRESULT_CP(result, m_array.resize(uSize));
		}
		return NRV_SUCCESS;
	}

	template<typename Type>
	NRESULT NVector<Type>::resize(NSize_t uSize)
	{
		if(uSize > m_array.size())
		{
			NRESULT result;
			NRESULT_CP(result, m_array.resize(uSize));
		}
		m_uSize = uSize;

		return NRV_SUCCESS;
	}
}