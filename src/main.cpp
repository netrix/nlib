#include "nTestGroupMemory.hpp"
#include "nTestGroupArray.hpp"

#include <tut_reporter.h>
#include "NLib/nLogger.hpp"

using namespace NLib;
using namespace Memory;

namespace tut
{
	test_runner_singleton runner;
}

int main()
{
	NLogInit("NLib.log");

	tut::reporter reporter;					// xml_reporter !!!

	tut::runner.get().set_callback(&reporter);
	tut::runner.get().run_tests();

	//tut::test_result result;
	//tut::runner.get().run_test("Array tests", 7, result);

	NMemoryInit();
	NSize_t* pSize = new (NMemoryGlobal) NSize_t;

	return !reporter.all_ok();
}