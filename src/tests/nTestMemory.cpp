#include <gtest/gtest.h>
#include <NLib/Memory/nMemory.hpp>
#include <NLib/Base/nAssert.hpp>

namespace
{
	// http://msinilo.pl/blog/?p=702
	template<size_t V>
	struct Log2
	{
		enum	{ Value = Log2<V / 2>::Value + 1 };
		typedef char V_MustBePowerOfTwo[((V & (V - 1)) == 0 ? 1 : -1)];
	};
	template<> struct Log2<1> { enum { Value = 0 }; };
}

class NTestMemory : public testing::Test
{
protected:
	NLib::NSize_t bytesToChunks(NLib::NSize_t bytes)
	{
		NAssert(bytes > 0, "Invalid value");
		return (bytes - 1) / sizeof(NLib::Memory::MemoryChunk) + 1;
	}

	// Tests
	void TestInit(NLib::NSize_t bytes)
	{
		EXPECT_EQ(NLib::NRV_SUCCESS, memoryObject.initMemory(bytes));
		EXPECT_EQ(1, memoryObject.getAllocatedChunksCount());
		EXPECT_EQ(bytesToChunks(bytes) + 1, memoryObject.getChunksCount());
	}

	void TestAllocate(NLib::NSize_t bytes)
	{
		const NLib::NSize_t INITIAL_ALLOC = 256;
		memoryObject.initMemory(INITIAL_ALLOC);

		void* pMemory = memoryObject.allocate(bytes);
		EXPECT_NE((void*)null, pMemory);
		EXPECT_GE(memoryObject.getAllocatedChunksCount(), bytesToChunks(bytes));
		EXPECT_GE(memoryObject.getChunksCount(), memoryObject.getAllocatedChunksCount());
	}

	template<NLib::NSize_t init, NLib::NSize_t alignment>
	void TestAlignment(NLib::NSize_t bytes)
	{
		const NLib::NSize_t INITIAL_ALLOC = init;
		memoryObject.initMemory(INITIAL_ALLOC);

		void* pMemory = memoryObject.allocate(bytes, alignment);
		EXPECT_NE((void*)null, pMemory);

		NLib::NSize_t uVal = (NLib::NSize_t)pMemory;
		NLib::NSize_t shift = Log2<alignment>::Value;
		EXPECT_EQ(((uVal >> shift) << shift), uVal);
	}

	NLib::Memory::NMemory memoryObject;
};

TEST_F(NTestMemory, Default)
{
	EXPECT_EQ(0, memoryObject.getAllocatedChunksCount());
	EXPECT_EQ(0, memoryObject.getChunksCount());
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
	TestInit(1);
}

TEST_F(NTestMemory, Init4)
{
	TestInit(4);
}

TEST_F(NTestMemory, Init8)
{
	TestInit(8);
}

TEST_F(NTestMemory, Init16)
{
	TestInit(16);
}

TEST_F(NTestMemory, Init256)
{
	TestInit(256);
}

TEST_F(NTestMemory, Init4681)
{
	TestInit(4681);
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
	TestAllocate(1);
}

TEST_F(NTestMemory, Allocate2)
{
	TestAllocate(2);
}

TEST_F(NTestMemory, Allocate4)
{
	TestAllocate(4);
}

TEST_F(NTestMemory, Allocate6)
{
	TestAllocate(6);
}

TEST_F(NTestMemory, Allocate8)
{
	TestAllocate(8);
}

TEST_F(NTestMemory, Allocate256)
{
	TestAllocate(256);
}

TEST_F(NTestMemory, Allocate4641)
{
	TestAllocate(4641);
}

TEST_F(NTestMemory, AllocateRelease41)
{
	memoryObject.initMemory(256);

	NLib::NSize_t uAllocated = memoryObject.getAllocatedChunksCount();

	void* pMemory = memoryObject.allocate(41);
	EXPECT_NE((void*)null, pMemory);

	memoryObject.release(pMemory);

	EXPECT_EQ(uAllocated, memoryObject.getAllocatedChunksCount());
}

TEST_F(NTestMemory, Reallocation)
{
	memoryObject.initMemory(256);

	void* pMemory = memoryObject.allocate(41);
	EXPECT_NE((void*)null, pMemory);

	memoryObject.release(pMemory);

	pMemory = memoryObject.allocate(413);
	EXPECT_NE((void*)null, pMemory);
}

// Aligned allocation tests
TEST_F(NTestMemory, AlignedAllocateAssert)
{
	memoryObject.initMemory(256);

	EXPECT_DEATH(memoryObject.allocate(41, 13), "uAlignment must be power of 2");
}

TEST_F(NTestMemory, AlignedAllocate2)
{
	TestAlignment<256, 2>(413);
}

TEST_F(NTestMemory, AlignedAllocate16)
{
	TestAlignment<256, 16>(41);
}

TEST_F(NTestMemory, AlignedAllocate256a)
{
	TestAlignment<1024, 256>(413);
}

TEST_F(NTestMemory, AlignedAllocate256b)
{
	TestAlignment<256, 256>(413);
}