#pragma once
#pragma warning(disable: 4512)

#include <tut/tut.hpp>
#include "NLib/Containers/nVector.hpp"

#define OMIT_ASSERTS_TESTS

namespace tut
{
	struct VectorTestData
	{
		NLib::Containers::NVector<NLib::NSize_t> vector;

		VectorTestData()
		{
			NLib::Memory::NMemoryInit(512);
		}

		~VectorTestData()
		{
			NLib::Memory::NMemory::ReleaseMemory();
		}
	};

	typedef test_group<VectorTestData>	tgVector;
	typedef tgVector::object			tgVectorObject;

	/**************************************************/
	// Not testing const/non-const functions
	template<>
	template<>
	void tgVectorObject::test<1>()
	{
		ensure_equals(vector.capacity(), 0);
		ensure_equals(vector.size(), 0);
		ensure_equals(vector.data(), (void*)null);
		ensure(vector.empty());
	}

	template<>
	template<>
	void tgVectorObject::test<2>()
	{
		vector.create(10);

		ensure_equals(vector.capacity(), 10);
		ensure_equals(vector.size(), 0);
		ensure(vector.data() != (void*)null);
		ensure(vector.empty());

		for(NLib::NSize_t i = 0; i < vector.capacity() - 1; ++i)
		{
			vector.push_back(i);
			ensure_equals(vector.size(), i + 1);
		}

		ensure_not(vector.empty());
		ensure_equals(vector.size(), 9);
		ensure_equals(vector.capacity(), 10);

		vector.release();

		ensure_equals(vector.capacity(), 0);
		ensure_equals(vector.size(), 0);
		ensure_equals(vector.data(), (void*)null);
		ensure(vector.empty());
	}

	template<>
	template<>
	void tgVectorObject::test<3>()
	{
		vector.create(10);

		ensure_equals(vector.capacity(), 10);
		ensure_equals(vector.size(), 0);
		ensure(vector.data() != null);
		ensure(vector.empty());

		vector.resize(20);

		ensure_equals(vector.size(), 20);
		ensure_not(vector.empty());

		vector.release();

		ensure_equals(vector.size(), 0);
		ensure_equals(vector.data(), (void*)null);
		ensure(vector.empty());
	}

	template<>
	template<>
	void tgVectorObject::test<4>()
	{
		vector.create(10);

		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(1);

		ensure_equals(vector.size(), 3);

		vector.pop_back();
		ensure_equals(vector.size(), 2);
		vector.pop_back();
		ensure_equals(vector.size(), 1);
		vector.pop_back();
		ensure_equals(vector.size(), 0);

		vector.release();
	}

	template<>
	template<>
	void tgVectorObject::test<5>()
	{
		vector.create(10);

		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(1);

		ensure_equals(vector.size(), 3);

		vector.clear();
		ensure_equals(vector.size(), 0);

		vector.release();
	}

	/**************************************************/
	// Object
	tgVector testGroupVector("Vector tests");
}