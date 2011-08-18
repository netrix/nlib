#pragma once
#pragma warning(disable: 4512)

#include <tut/tut.hpp>
#include "NLib/Containers/nVector.hpp"

#define OMIT_ASSERTS_TESTS

namespace tut
{
	struct VectorTestData
	{
		NLib::Containers::NVector<NLib::NSize_t> array;

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
	}

	/**************************************************/
	// Object
	tgArray testGroupVector("Vector tests");
}