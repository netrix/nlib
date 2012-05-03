set(HPP nArguments.hpp
		nCommandWalker.hpp)

set(CPP nArguments.cpp
		nCommandWalker.cpp)

set(NAME "ncmdlineparser")

add_library(${NAME} ${CPP})

install(FILES ${HPP} DESTINATION include/NLib/CmdLineParser)
install(TARGETS ${NAME} DESTINATION lib)
