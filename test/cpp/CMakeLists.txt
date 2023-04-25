cmake_minimum_required(VERSION 3.21)

add_executable(unit_tests.cjs Tests.cpp)

target_include_directories(unit_tests.cjs PRIVATE ../../src/cpp)

target_link_libraries(unit_tests.cjs math)

add_test(NAME unit_tests COMMAND node unit_tests.cjs)