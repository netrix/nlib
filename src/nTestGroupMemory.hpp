#pragma once
#pragma warning(disable: 4512)

#include <tut/tut.hpp>
#include "NLib/nMemory.hpp"

#define OMIT_ASSERTS_TESTS

namespace tut
{
	struct MemoryTestData
	{
		NIne::NMemory memoryObject;
	};

	typedef test_group<MemoryTestData>	tg;
	typedef tg::object					tgObject;

	/**************************************************/
	// Initiation tests
	template<>
	template<>
	void tgObject::test<1>()
	{
	#ifndef OMIT_ASSERTS_TESTS
		memoryObject.initMemory(0); // Raises an assert
	#endif
	}

	template<>
	template<>
	void tgObject::test<2>()
	{
		ensure_equals(memoryObject.initMemory(1), NIne::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgObject::test<3>()
	{
		ensure_equals(memoryObject.initMemory(4), NIne::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgObject::test<4>()
	{
		ensure_equals(memoryObject.initMemory(8), NIne::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgObject::test<5>()
	{
		ensure_equals(memoryObject.initMemory(16), NIne::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgObject::test<6>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgObject::test<7>()
	{
		ensure_equals(memoryObject.initMemory(4681), NIne::NRV_SUCCESS);
	}

	template<>
	template<>
	void tgObject::test<8>()
	{
		ensure_equals(memoryObject.initMemory(467489481), NIne::NRV_SUCCESS);
	}

	/**************************************************/
	// Memory release tests
	template<>
	template<>
	void tgObject::test<9>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);
		memoryObject.releaseMemory();
	}

	/**************************************************/
	// Allocation tests
	template<>
	template<>
	void tgObject::test<10>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

	#ifndef OMIT_ASSERTS_TESTS
		memoryObject.allocate(0);		// Raises an assert
	#endif
	}

	template<>
	template<>
	void tgObject::test<11>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(1);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgObject::test<12>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(2);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgObject::test<13>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(4);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgObject::test<14>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(6);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgObject::test<15>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(8);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgObject::test<16>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(256);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgObject::test<17>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(4641);
		ensure(pMemory != null);
	}

	/**************************************************/
	// Allocated release tests
	template<>
	template<>
	void tgObject::test<18>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(41);
		ensure(pMemory != null);

		memoryObject.release(pMemory);
	}

	template<>
	template<>
	void tgObject::test<19>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(413);
		ensure(pMemory != null);

		memoryObject.release(pMemory);
	}

	template<>
	template<>
	void tgObject::test<20>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(41);
		ensure(pMemory != null);

		memoryObject.release(pMemory);

		pMemory = memoryObject.allocate(413);
		ensure(pMemory != null);
	}

	template<>
	template<>
	void tgObject::test<21>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

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
	void tgObject::test<22>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(41, 13);
	}

	template<>
	template<>
	void tgObject::test<23>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(413, 2);
		ensure(pMemory != null);

		NIne::NSize_t uVal = (NIne::NSize_t)pMemory;
		ensure(((uVal >> 1) << 1) == uVal);
	}

	template<>
	template<>
	void tgObject::test<24>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(41, 16);
		ensure(pMemory != null);

		NIne::NSize_t uVal = (NIne::NSize_t)pMemory;
		ensure(((uVal >> 4) << 4) == uVal);
	}

	template<>
	template<>
	void tgObject::test<25>()
	{
		ensure_equals(memoryObject.initMemory(256), NIne::NRV_SUCCESS);

		void* pMemory = memoryObject.allocate(413, 256);
		ensure(pMemory != null);

		NIne::NSize_t uVal = (NIne::NSize_t)pMemory;
		ensure(((uVal >> 8) << 8) == uVal);
	}

	/**************************************************/
	// Object
	tg testGroupMemory("Memory manager tests");
}