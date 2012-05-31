set(NAME nlib-tests)

#set(HPP	)

set(CPP main.cpp
		nTestMemory.cpp
		nTestArray.cpp
		nTestVector.cpp
		nTestQueue.cpp)

set(DEPENDENCIES nbase
				 nmemory
				 gtest)

add_executable(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} ${DEPENDENCIES})
