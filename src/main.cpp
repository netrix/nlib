#include <stdio.h>
#include "NLib/nMemory.hpp"
using namespace NIne;

int main()
{
	NMemory::m_instance.initMemory(256);

	void* pMemory = NMemory::m_instance.allocate(128);

	NMemory::m_instance.release(pMemory);

	return 0;
}