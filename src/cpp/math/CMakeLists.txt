cmake_minimum_required(VERSION 3.21)

add_library(math
	coordinates.cpp
	trigonometry.cpp
)

target_precompile_headers(math INTERFACE
	math.hpp
	matrix.hpp
	vector.hpp
	projection_matrix.hpp
)