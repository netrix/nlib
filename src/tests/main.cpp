#include <gtest/gtest.h>
#include <NLib/Base/nAssert.hpp>
#include <NLib/Base/nLogger.hpp>

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	NLib::NAssert_StdAssert(true);
	return RUN_ALL_TESTS();
}