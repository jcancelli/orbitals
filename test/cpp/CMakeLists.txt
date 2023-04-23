cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_COMPILER clang++)

add_executable(unit_tests Tests.cpp)

target_include_directories(unit_tests PRIVATE ../../src/cpp)