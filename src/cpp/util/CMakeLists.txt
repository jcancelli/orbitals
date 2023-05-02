cmake_minimum_required(VERSION 3.21)

add_library(util
	fetch.cpp
)

target_precompile_headers(util INTERFACE 
	assert.hpp
)