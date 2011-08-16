#pragma once
#pragma warning(disable: 4512)

#include <tut/tut.hpp>
#include "NLib/nArray.hpp"

#define OMIT_ASSERTS_TESTS

namespace tut
{
	struct ArrayTestData
	{
		NIne::NArray<NIne::NSize_t> array;

		ArrayTestData()
		{
			NIne::NMemoryInit(512);
		}

		~ArrayTestData()
		{
			NIne::NMemoryReleaseAll();
		}
	};

	typedef test_group<ArrayTestData>	tgArray;
	typedef tgArray::object				tgArrayObject;

	/**************************************************/
	// Not testing const/non-const functions
	template<>
	template<>
	void tgArrayObject::test<1>()
	{
		ensure_equals("Not initializated size validation", array.size(), 0);
	}

	template<>
	template<>
	void tgArrayObject::test<2>()
	{
		ensure("Not initializated data validation", array.data() == null);
	}

	template<>
	template<>
	void tgArrayObject::test<3>()
	{
		ensure_not("Not initializated operator bool validation", array);
	}

	template<>
	template<>
	void tgArrayObject::test<4>()
	{
		array.create(20);
		ensure_equals("Initializated size validation", array.size(), 20);

		array.release();
		ensure_equals("Initializated size validation after release", array.size(), 0);
	}

	template<>
	template<>
	void tgArrayObject::test<5>()
	{
		array.create(20);
		ensure("Initializated data validation", array.data() != null);

		array.release();
		ensure("Initializated data validation", array.data() == null);
	}

	template<>
	template<>
	void tgArrayObject::test<6>()
	{
		array.create(20);
		ensure("Initializated operator bool validation", array);

		array.release();
		ensure_not("Initializated operator bool validation", array);
	}

	template<>
	template<>
	void tgArrayObject::test<7>()
	{
		array.create(20);

		array.resize(41);
		ensure_equals("Resize validation after resize", array.size(), 41);

		array.release();
	}

	template<>
	template<>
	void tgArrayObject::test<8>()
	{
		array.create(20);

		for(NIne::NSize_t i = 0; i < array.size(); ++i)
		{
			ensure_equals("Access operators tests", &array[i], array.data() + i);
			array[i] = 2 * i + 1;
		}

		array.release();
	}

	/**************************************************/
	// Memory manger response to array (if it release memory correctly
	template<>
	template<>
	void tgArrayObject::test<9>()
	{
		NIne::NSize_t uChunks = NIne::NMemoryGetAllocatedChunksCount();

		array.create(20);
		ensure("Acquire memory validation", NIne::NMemoryGetAllocatedChunksCount() > uChunks);

		array.release();
		ensure_equals("Release memory validations", NIne::NMemoryGetAllocatedChunksCount(), uChunks);
	}

	/**************************************************/
	// Object
	tgArray testGroupArray("Array tests");
}