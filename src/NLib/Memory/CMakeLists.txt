set(HPP nMemory.hpp
		nMemoryGuard.hpp)

set(CPP nMemory.cpp)

set(NAME "nmemory")

add_library(${NAME} ${CPP})

install(FILES ${HPP} DESTINATION include/NLib/Memory)
install(TARGETS ${NAME} DESTINATION lib)
