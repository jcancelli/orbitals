cmake_minimum_required(VERSION 3.21)

project(orbitals CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER em++)

enable_testing()

include_directories(/boost_1_82_0)

add_subdirectory(./src/cpp/)

if (BUILD_TESTING)
	add_subdirectory(./test/cpp/)
endif()
