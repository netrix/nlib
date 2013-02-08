set(SOURCES nArray.hpp
		nContainerGuard.hpp
		nQueue.hpp
		nStableVector.hpp
		nVector.hpp)

set(NAME "ncontainers")

add_custom_target(${NAME} SOURCES ${SOURCES})
		
install(FILES ${SOURCES} DESTINATION include/NLib/Containers)
