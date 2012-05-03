set(HPP nMMatrix.inl
		nMTransfoms.inl
		nMUtilities.inl
		nMVector.inl
		nMVector2f.inl
		nMVector3f.inl
		nMVector4f.inl
		nMath.hpp)

set(CPP nMath.cpp)

set(NAME "nmath")

add_library(${NAME} ${CPP})

install(FILES ${HPP} DESTINATION include/NLib/Math)
install(TARGETS ${NAME} DESTINATION lib)
