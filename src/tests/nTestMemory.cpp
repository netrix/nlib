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
	EXPECT_EQ(memoryObject.initMemory(1), NLib::NRV_SUCCESS);
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 1);
	EXPECT_EQ(memoryObject.getChunksCount(), 2);
}

TEST_F(NTestMemory, Init4)
{
	EXPECT_EQ(memoryObject.initMemory(4), NLib::NRV_SUCCESS);
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 1);
	EXPECT_EQ(memoryObject.getChunksCount(), 2);
}

TEST_F(NTestMemory, Init8)
{
	EXPECT_EQ(memoryObject.initMemory(8), NLib::NRV_SUCCESS);
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 1);
	EXPECT_EQ(memoryObject.getChunksCount(), 2);
}

TEST_F(NTestMemory, Init16)
{
	EXPECT_EQ(memoryObject.initMemory(16), NLib::NRV_SUCCESS);
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 1);
	EXPECT_EQ(memoryObject.getChunksCount(), 2);
}

TEST_F(NTestMemory, Init256)
{
	EXPECT_EQ(memoryObject.initMemory(256), NLib::NRV_SUCCESS);
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 1);
	EXPECT_EQ(memoryObject.getChunksCount(), 17);
}

TEST_F(NTestMemory, Init4681)
{
	EXPECT_EQ(memoryObject.initMemory(4681), NLib::NRV_SUCCESS);
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 1);
	EXPECT_EQ(memoryObject.getChunksCount(), 294);
}

TEST_F(NTestMemory, Init467489481)
{
	EXPECT_EQ(memoryObject.initMemory(467489481), NLib::NRV_SUCCESS);
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 1);
	EXPECT_EQ(memoryObject.getChunksCount(), 29218094);
}

TEST_F(NTestMemory, Release)
{
	memoryObject.initMemory(256);
	memoryObject.releaseMemory();

	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 0);
	EXPECT_EQ(memoryObject.getChunksCount(), 0);
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
	EXPECT_NE(pMemory, (void*)null);
	EXPECT_EQ(memoryObject.getAllocatedChunksCount(), 2);
	EXPECT_EQ(memoryObject.getChunksCount(), 17);
}