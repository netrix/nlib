#include "nTestGroupMemory.hpp"

#include <tut_reporter.h>
#include "NLib/nLogger.hpp"

using namespace NIne;

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
	//tut::runner.get().run_test("Memory manager tests", 23, result);

	return !reporter.all_ok();
}