#include <gtest/gtest.h>
#include <NLib/Containers/nVector.hpp>

class NTestVector : public testing::Test
{
protected:
	NTestVector()
	{
		NLib::Memory::NMemory::InitMemory(512);
	}

	~NTestVector()
	{
		NLib::Memory::NMemory::ReleaseMemory();
	}

protected:
	NLib::Containers::NVector<NLib::NSize_t> vector;
};

TEST_F(NTestVector, Empty)
{
	EXPECT_EQ(0, vector.capacity());
	EXPECT_EQ(0, vector.size());
	EXPECT_EQ((void*)0, vector.data());
	EXPECT_TRUE(vector.empty());
}

TEST_F(NTestVector, CreateAddRelease)
{
	const NLib::NSize_t TEST_SIZE = 10;
	vector.create(TEST_SIZE);

	// Check allocated
	EXPECT_EQ(TEST_SIZE, vector.capacity());
	EXPECT_EQ(0, vector.size());
	EXPECT_NE((void*)0, vector.data());
	EXPECT_TRUE(vector.empty());

	// Add
	for(NLib::NSize_t i = 0; i < vector.capacity() - 1; ++i)
	{
		vector.push_back(i);
		EXPECT_EQ(i + 1, vector.size());
	}

	// Check filled
	EXPECT_FALSE(vector.empty());
	EXPECT_EQ(TEST_SIZE - 1, vector.size());
	EXPECT_EQ(TEST_SIZE, vector.capacity());

	vector.release();

	// Check released
	EXPECT_EQ(0, vector.capacity());
	EXPECT_EQ(0, vector.size());
	EXPECT_EQ((void*)0, vector.data());
	EXPECT_TRUE(vector.empty());
}

TEST_F(NTestVector, Resize)
{
	const NLib::NSize_t TEST_SIZE_1 = 10;
	const NLib::NSize_t TEST_SIZE_2 = 20;
	vector.create(TEST_SIZE_1);

	// Check allocated
	EXPECT_EQ(TEST_SIZE_1, vector.capacity());
	EXPECT_EQ(0, vector.size());
	EXPECT_NE((void*)0, vector.data());
	EXPECT_TRUE(vector.empty());

	vector.resize(TEST_SIZE_2);

	// Check resized
	EXPECT_EQ(TEST_SIZE_2, vector.size());
	EXPECT_FALSE(vector.empty());

	vector.release();
}

TEST_F(NTestVector, PushPop)
{
	const NLib::NSize_t TEST_SIZE = 10;
	vector.create(TEST_SIZE);

	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(1);

	EXPECT_EQ(3, vector.size());

	vector.pop_back();
	EXPECT_EQ(2, vector.size());
	vector.pop_back();
	EXPECT_EQ(1, vector.size());
	vector.pop_back();
	EXPECT_EQ(0, vector.size());

	vector.release();
}

TEST_F(NTestVector, Clear)
{
	const NLib::NSize_t TEST_SIZE = 10;
	vector.create(TEST_SIZE);

	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(1);

	EXPECT_EQ(3, vector.size());

	vector.clear();
	EXPECT_EQ(0, vector.size());

	vector.release();
}