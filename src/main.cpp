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

	return !reporter.all_ok();
}