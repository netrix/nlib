
set(NBASE src/Base/nAssert.cpp 
		  src/Base/nLogger.cpp)

set(NMATH src/Math/nMath.cpp)

set(NMEMORY src/Memory/nMemory.cpp)

set(NFILES ${NBASE} ${NMATH} ${NMEMORY})

include_directories(".")
add_library(nlibbase ${NFILES})
