#pragma once
#pragma warning(disable: 4512)

#include <tut/tut.hpp>
#include <NLib/Memory/nMemory.hpp>

#define OMIT_ASSERTS_TESTS

namespace tut
{
	struct MemoryTestData
	{
		NLib::Memory::NMemory memoryObject;
	};

	typedef test_group<MemoryTestData>	tgMemory;
	typedef tgMemory::object			tgMemoryObject;

	/**************************************************/

	template<>
	template<>
	void tgMemoryObject::test<23>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(413, 2);
		ensure(pMemory != null);

		NLib::NSize_t uVal = (NLib::NSize_t)pMemory;
		ensure(((uVal >> 1) << 1) == uVal);
	}

	template<>
	template<>
	void tgMemoryObject::test<24>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(41, 16);
		ensure(pMemory != null);

		NLib::NSize_t uVal = (NLib::NSize_t)pMemory;
		ensure(((uVal >> 4) << 4) == uVal);
	}

	template<>
	template<>
	void tgMemoryObject::test<25>()
	{
		ensure_equals(memoryObject.initMemory(1024), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(413, 256);
		ensure(pMemory != null);

		NLib::NSize_t uVal = (NLib::NSize_t)pMemory;
		ensure(((uVal >> 8) << 8) == uVal);
	}

	template<>
	template<>
	void tgMemoryObject::test<26>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(413, 256);
		ensure(pMemory != null);

		NLib::NSize_t uVal = (NLib::NSize_t)pMemory;
		ensure(((uVal >> 8) << 8) == uVal);
	}

	/**************************************************/
	// info functions tests
	template<>
	template<>
	void tgMemoryObject::test<27>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);
		NLib::NSize_t uChunks = memoryObject.getChunksCount();
		void* pMemory = memoryObject.allocate(413, 256);

		ensure(uChunks < memoryObject.getChunksCount());
	}

	template<>
	template<>
	void tgMemoryObject::test<28>()
	{
		ensure_equals(memoryObject.initMemory(1024), NLib::NRV_SUCCESS);

		NLib::NSize_t uChunks = memoryObject.getAllocatedChunksCount();
		void* pMemory = memoryObject.allocate(413, 256);

		ensure(uChunks < memoryObject.getAllocatedChunksCount());
		memoryObject.release(pMemory);
		//ensure(uChunks == memoryObject.getAllocatedChunksCount());
	}

	/**************************************************/
	// Object
	tgMemory testGroupMemory("Memory manager tests");
}