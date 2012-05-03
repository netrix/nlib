set(HPP nAssert.hpp
		nBase.hpp
		nErrors.hpp
		nLogger.hpp)

set(CPP nAssert.cpp
		nLogger.cpp)

set(NAME "nbase")

add_library(${NAME} ${CPP})

install(FILES ${HPP} DESTINATION include/NLib/Base)
install(TARGETS ${NAME} DESTINATION lib)
