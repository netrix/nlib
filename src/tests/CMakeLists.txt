set(NAME nlib-tests)

set(HPP nTestGroupArray.hpp
		nTestGroupVector.hpp
		nTestGroupQueue.hpp)

set(CPP main.cpp
		nTestMemory.cpp)

set(DEPENDENCIES nbase
				 nmemory
				 gtest)

add_executable(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} ${DEPENDENCIES})
