add_subdirectory(NLib)

if(${BUILD_UNITTESTS})
	add_subdirectory(tests)
endif()
