cmake_minimum_required(VERSION 3.21)

project(orbitals CXX)

set(CMAKE_CXX_STANDARD 20)

add_link_options(
	-sFETCH
	-sASYNCIFY
	-sUSE_WEBGL2=1
	-sMIN_WEBGL_VERSION=2
	-sALLOW_MEMORY_GROWTH=1
	-lembind
)

add_subdirectory(./src/cpp/)