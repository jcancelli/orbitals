cmake_minimum_required(VERSION 3.21)

add_library(engine
	application.cpp
	camera.cpp
	camera_movement.cpp
	clock.cpp
	debug.cpp
	index_buffer.cpp
	inputs.cpp
	keyboard.cpp
	material.cpp
	mesh.cpp
	mouse.cpp
	scene.cpp
	shader.cpp
	transform.cpp
	vertex_array.cpp
	vertex_layout.cpp
	vertex.cpp
	viewport.cpp
	primitives/gl_object.cpp
	primitives/texture.cpp
)