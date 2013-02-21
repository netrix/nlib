set(SOURCES
   nCommon.hpp
   nClient.hpp
   nClient.cpp
   nServer.hpp
   nServer.cpp
)

set(NAME "nsockets")

add_library(${NAME} ${SOURCES})

install(FILES ${HPP} DESTINATION include/NLib/Sockets)
install(TARGETS ${NAME} DESTINATION lib)

# For Visual Studio
source_group(src FILES ${SOURCES})