set(NAME nlib-tests)

set(HPP nTestGroupVector.hpp
		nTestGroupQueue.hpp)

set(CPP main.cpp
		nTestMemory.cpp
		nTestArray.cpp
		nTestVector.cpp)

set(DEPENDENCIES nbase
				 nmemory
				 gtest)

add_executable(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} ${DEPENDENCIES})
