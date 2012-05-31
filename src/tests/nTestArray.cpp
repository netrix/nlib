#include <gtest/gtest.h>
#include <NLib/Containers/nArray.hpp>

class NTestArray : public testing::Test
{
protected:
	NTestArray()
	{
		NLib::Memory::NMemory::InitMemory(512);
	}

	~NTestArray()
	{
		NLib::Memory::NMemory::ReleaseMemory();
	}

protected:
	NLib::Containers::NArray<NLib::NSize_t> array;
};

TEST_F(NTestArray, Empty)
{
	EXPECT_EQ(0, array.size());
	EXPECT_EQ((void*)0, array.data());
	EXPECT_FALSE(array);
}

TEST_F(NTestArray, CreateRelease)
{
	const NLib::NSize_t TEST_SIZE = 20;

	array.create(TEST_SIZE);
	EXPECT_EQ(TEST_SIZE, array.size());
	EXPECT_NE((void*)0, array.data());
	EXPECT_TRUE(array);

	array.release();
	EXPECT_EQ(0, array.size());
	EXPECT_EQ((void*)0, array.data());
	EXPECT_FALSE(array);
}

TEST_F(NTestArray, Resize)
{
	const NLib::NSize_t TEST_SIZE_1 = 20;
	const NLib::NSize_t TEST_SIZE_2 = 42;

	array.create(TEST_SIZE_1);
	array.resize(TEST_SIZE_2);
	EXPECT_EQ(TEST_SIZE_2, array.size());

	array.release();
}

TEST_F(NTestArray, AccessOperators)
{
	const NLib::NSize_t TEST_SIZE = 20;
	array.create(TEST_SIZE);

	for(NLib::NSize_t i = 0; i < array.size(); ++i)
	{
		EXPECT_EQ(&array[i], array.data() + i);
		array[i] = 2 * i + 1;
	}

	array.release();
}