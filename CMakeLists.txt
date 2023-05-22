cmake_minimum_required(VERSION 3.21)

project(orbitals CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER em++)

find_package(Boost 1.81.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

if(DEBUG_MODE)
	message("Building in debug mode")
	add_definitions(-DDEBUG_MODE)
endif()

include(CTest)

add_subdirectory(./src/cpp/)

if (BUILD_TESTING)
	add_subdirectory(./test/cpp/)
endif()
