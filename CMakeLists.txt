cmake_minimum_required(VERSION 2.8)
project(NLib)

# Tests
option(BUILD_UNITTESTS "Build Unit tests" 0)

if(${NLIB_BUILD_UNITTESTS})
	add_subdirectory(modules/gtest)
	include_directories(modules/gtest/include)
endif()

# Project files
include_directories(src)

add_subdirectory(src)