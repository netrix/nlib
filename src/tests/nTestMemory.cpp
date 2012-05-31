#include <gtest/gtest.h>

#define NSTD_ASSERT
#include <NLib/Memory/nMemory.hpp>

class NTestMemory : public testing::Test
{
protected:
	NLib::Memory::NMemory memoryObject;
};

TEST_F(NTestMemory, Default)
{
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 0);
	EXPECT_EQ(memoryObject.getChunksCount(), 0);
}

TEST_F(NTestMemory, EmptyInit)
{
	EXPECT_DEATH(memoryObject.initMemory(0), "Invalid parameter");
}

TEST_F(NTestMemory, DoubleInit)
{
	memoryObject.initMemory(1);
	EXPECT_DEATH(memoryObject.initMemory(1), "Double initialization");
}

TEST_F(NTestMemory, Init1)
{
	EXPECT_EQ(NLib::NRV_SUCCESS, memoryObject.initMemory(1));
	EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(2, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Init4)
{
	EXPECT_EQ(NLib::NRV_SUCCESS, memoryObject.initMemory(4));
	EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(2, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Init8)
{
	EXPECT_EQ(NLib::NRV_SUCCESS, memoryObject.initMemory(8));
	EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(2, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Init16)
{
	EXPECT_EQ(NLib::NRV_SUCCESS, memoryObject.initMemory(16));
	EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(2, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Init256)
{
	EXPECT_EQ(NLib::NRV_SUCCESS, memoryObject.initMemory(256));
	EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Init4681)
{
	EXPECT_EQ(NLib::NRV_SUCCESS, memoryObject.initMemory(4681));
	EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(294, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Release)
{
	memoryObject.initMemory(256);
	memoryObject.releaseMemory();

	EXPECT_EQ(0, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(0, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Allocate0)
{
	memoryObject.initMemory(256);

	EXPECT_DEATH(memoryObject.allocate(0), "Invalid parameter");
}

TEST_F(NTestMemory, Allocate1)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(1);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(2, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Allocate2)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(2);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(2, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Allocate4)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(4);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(2, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Allocate6)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(6);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(2, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Allocate8)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(8);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(2, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Allocate256)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(256);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(19, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(35, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Allocate4641)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(4641);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(293, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(309, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, AllocateRelease41)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(41);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(5, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());

	memoryObject.release(pMemory);

	EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, Reallocation)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(41);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(5, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());

	memoryObject.release(pMemory);

	EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(17, memoryObject.getChunksCount());

	pMemory = memoryObject.allocate(413);

	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(29, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(45, memoryObject.getChunksCount());
}

TEST_F(NTestMemory, ReallocationSwapped)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(413);
	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(29, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(45, memoryObject.getChunksCount());

	memoryObject.release(pMemory);

	EXPECT_EQ(2, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(45, memoryObject.getChunksCount());

	pMemory = memoryObject.allocate(41);

	EXPECT_NE((void*)null, pMemory);
	EXPECT_EQ(6, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(45, memoryObject.getChunksCount());
}

// Aligned allocation tests
TEST_F(NTestMemory, AlignedAllocateAssert)
{
	memoryObject.initMemory(256);

	EXPECT_DEATH(memoryObject.allocate(41, 13), "uAlignment must be power of 2");
}