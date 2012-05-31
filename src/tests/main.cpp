#include <gtest/gtest.h>
#include <NLib/Base/nAssert.hpp>
#include <NLib/Base/nLogger.hpp>

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	NAssert_StdAssert(true);

	bool val = [&argc](int a, int b){ return a < b; }(1, 2);

	return RUN_ALL_TESTS();
}