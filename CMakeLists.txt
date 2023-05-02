cmake_minimum_required(VERSION 3.21)

project(orbitals CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER em++)

set(BOOST_ROOT /boost_1_82_0)

find_package(Boost 1.82.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

add_subdirectory(./src/cpp/)

if (BUILD_TESTING)
	add_subdirectory(./test/cpp/)
endif()
