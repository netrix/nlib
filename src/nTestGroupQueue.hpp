#pragma once
#pragma warning(disable: 4512)

#include <tut/tut.hpp>
#include "NLib/Containers/nQueue.hpp"

#define OMIT_ASSERTS_TESTS

namespace tut
{
	struct QueueTestData
	{
		NLib::Containers::NQueue<NLib::NSize_t> vector;

		QueueTestData()
		{
			NLib::Memory::NMemoryInit(512);
		}

		~QueueTestData()
		{
			NLib::Memory::NMemory::ReleaseMemory();
		}
	};

	typedef test_group<QueueTestData>	tgQueue;
	typedef tgQueue::object				tgQueueObject;

	/**************************************************/
	// Not testing const/non-const functions
	template<>
	template<>
	void tgQueueObject::test<1>()
	{
	}

	/**************************************************/
	// Object
	tgQueue testGroupQueue("Queue tests");
}