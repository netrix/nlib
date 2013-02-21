set(SOURCES
   nCommon.hpp
   nClientSocket.hpp
   nClientSocket.cpp
   nServerSocket.hpp
   nServerSocket.cpp
)

set(NAME "nsockets")

add_library(${NAME} ${SOURCES})

install(FILES ${HPP} DESTINATION include/NLib/Sockets)
install(TARGETS ${NAME} DESTINATION lib)

# For Visual Studio
source_group(src FILES ${SOURCES})