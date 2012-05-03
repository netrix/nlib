set(HPP nSockets.hpp)

set(CPP nSockets.cpp)

set(NAME "nsockets")

add_library(${NAME} ${CPP})

install(FILES ${HPP} DESTINATION include/NLib/Sockets)
install(TARGETS ${NAME} DESTINATION lib)
