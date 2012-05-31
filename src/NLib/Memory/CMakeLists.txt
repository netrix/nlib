set(HPP nMemory.hpp
		nMemoryGuard.hpp)

set(CPP nMemory.cpp)

set(NAME "nmemory")

add_library(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} nbase)

install(FILES ${HPP} DESTINATION include/NLib/Memory)
install(TARGETS ${NAME} DESTINATION lib)
