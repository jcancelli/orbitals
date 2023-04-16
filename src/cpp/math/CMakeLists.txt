cmake_minimum_required(VERSION 3.21)

add_library(math INTERFACE)

target_precompile_headers(math INTERFACE
	math.hpp
	matrix.hpp
	trigonometry.hpp
	vector.hpp
	view_matrix.hpp
)