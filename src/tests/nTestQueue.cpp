#include <gtest/gtest.h>
#include <NLib/Containers/nQueue.hpp>

class NTestQueue : public testing::Test
{
protected:
	NTestQueue()
	{
		NLib::Memory::NMemory::InitMemory(512);
	}

	~NTestQueue()
	{
		NLib::Memory::NMemory::ReleaseMemory();
	}

protected:
	NLib::Containers::NQueue<NLib::NSize_t> queue;
};

TEST_F(NTestQueue, Empty)
{
	EXPECT_EQ(0, queue.capacity());
	EXPECT_EQ(0, queue.size());
	EXPECT_TRUE(queue.empty());
}