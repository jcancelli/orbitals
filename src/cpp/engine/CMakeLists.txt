cmake_minimum_required(VERSION 3.21)

add_library(engine
	application.cpp
	camera.cpp
	camera_movement.cpp
	clock.cpp
	inputs.cpp
	keyboard.cpp
	material.cpp
	mesh.cpp
	mouse.cpp
	scene.cpp
	viewport.cpp
	primitives/debug.cpp
	primitives/gl_object.cpp
	primitives/index_buffer.cpp
	primitives/shader.cpp
	primitives/texture.cpp
	primitives/transform.cpp
	primitives/vertex_array.cpp
	primitives/vertex_layout.cpp
	primitives/vertex.cpp
)