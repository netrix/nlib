#pragma once
#pragma warning(disable: 4512)

#include <tut/tut.hpp>
#include "NLib/Memory/nMemory.hpp"

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
	// Initiation tests
	template<>
	template<>
	void tgMemoryObject::test<1>()
	{
	#ifndef OMIT_ASSERTS_TESTS
		memoryObject.initMemory(0); // Raises an assert
	#endif
	}

	template<>
	template<>
	void tgMemoryObject::test<2>()
	{
		ensure_equals(memoryObject.initMemory(1), NLib::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgMemoryObject::test<3>()
	{
		ensure_equals(memoryObject.initMemory(4), NLib::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgMemoryObject::test<4>()
	{
		ensure_equals(memoryObject.initMemory(8), NLib::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgMemoryObject::test<5>()
	{
		ensure_equals(memoryObject.initMemory(16), NLib::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgMemoryObject::test<6>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgMemoryObject::test<7>()
	{
		ensure_equals(memoryObject.initMemory(4681), NLib::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgMemoryObject::test<8>()
	{
		ensure_equals(memoryObject.initMemory(467489481), NLib::NRV_SUCCESS);
	}

	/**************************************************/
	// Memory release tests
	template<>
	template<>
	void tgMemoryObject::test<9>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);
		memoryObject.releaseMemory();
	}

	/**************************************************/
	// Allocation tests
	template<>
	template<>
	void tgMemoryObject::test<10>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

	#ifndef OMIT_ASSERTS_TESTS
		memoryObject.allocate(0);		// Raises an assert
	#endif
	}

	template<>
	template<>
	void tgMemoryObject::test<11>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(1);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgMemoryObject::test<12>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(2);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgMemoryObject::test<13>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(4);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgMemoryObject::test<14>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(6);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgMemoryObject::test<15>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(8);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgMemoryObject::test<16>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(256);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgMemoryObject::test<17>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(4641);
		ensure(pMemory != null);
	}

	/**************************************************/
	// Allocated release tests
	template<>
	template<>
	void tgMemoryObject::test<18>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(41);
		ensure(pMemory != null);

		memoryObject.release(pMemory);
	}

	template<>
	template<>
	void tgMemoryObject::test<19>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(413);
		ensure(pMemory != null);

		memoryObject.release(pMemory);
	}

	template<>
	template<>
	void tgMemoryObject::test<20>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(41);
		ensure(pMemory != null);

		memoryObject.release(pMemory);

		pMemory = memoryObject.allocate(413);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgMemoryObject::test<21>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(413);
		ensure(pMemory != null);

		memoryObject.release(pMemory);

		pMemory = memoryObject.allocate(41);
		ensure(pMemory != null);
	}

	/**************************************************/
	// Aligned allocation tests
	template<>
	template<>
	void tgMemoryObject::test<22>()
	{
		ensure_equals(memoryObject.initMemory(256), NLib::NRV_SUCCESS);

	#ifndef OMIT_ASSERTS_TESTS
		void* pMemory = memoryObject.allocate(41, 13);
	#endif
	}

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