add_subdirectory(NLib)

if(${NLIB_BUILD_UNITTESTS})
	add_subdirectory(tests)
endif()
