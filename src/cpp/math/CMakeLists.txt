cmake_minimum_required(VERSION 3.21)

add_library(math
	coordinates.cpp
	SphericalHarmonics.cpp
	trigonometry.cpp
)

target_precompile_headers(math INTERFACE
	matrix.hpp
	vector.hpp
	projection_matrix.hpp
)