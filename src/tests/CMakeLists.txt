set(NAME nlib-tests)

set(HPP nTestGroupMemory.hpp
		nTestGroupArray.hpp
		nTestGroupVector.hpp
		nTestGroupQueue.hpp)

set(CPP main.cpp
		nTestMemory.cpp)

set(DEPENDECIES nbase
				nmemory

				gtest)

add_executable(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} ${DEPENDECIES})
