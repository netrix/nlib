set(HPP nBitmap.hpp)

set(CPP nBitmap.cpp)

set(NAME "nimages")

add_library(${NAME} ${CPP})

install(FILES ${HPP} DESTINATION include/NLib/Images)
install(TARGETS ${NAME} DESTINATION lib)
