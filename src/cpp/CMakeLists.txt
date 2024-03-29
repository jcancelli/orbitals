cmake_minimum_required(VERSION 3.21)

add_link_options(
	-sFETCH
	-sASYNCIFY
	-sUSE_WEBGL2=1
	-sMIN_WEBGL_VERSION=2
	-sALLOW_MEMORY_GROWTH=1
	-sENVIRONMENT=web
	-lembind
	--preload-file ${orbitals_SOURCE_DIR}/src/cpp/assets/@/
)

include_directories(libraries)

add_subdirectory(math)
add_subdirectory(util)
add_subdirectory(engine)
add_subdirectory(libraries)
add_subdirectory(widget)

add_executable(wasm.mjs orbitals.cpp orbital.cpp)

target_link_libraries(wasm.mjs math)
target_link_libraries(wasm.mjs util)
target_link_libraries(wasm.mjs engine)
target_link_libraries(wasm.mjs imgui)
target_link_libraries(wasm.mjs stb)
target_link_libraries(wasm.mjs widget)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/wasm.mjs
	DESTINATION src/frontend/lib/wasm/
	PERMISSIONS OWNER_READ OWNER_WRITE
)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/wasm.wasm
	DESTINATION static/
	PERMISSIONS OWNER_READ OWNER_WRITE
)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/wasm.data
	DESTINATION static/
	PERMISSIONS OWNER_READ OWNER_WRITE
)