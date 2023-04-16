cmake_minimum_required(VERSION 3.21)

add_subdirectory(math)
add_subdirectory(util)
add_subdirectory(engine)

add_executable(wasm.mjs main.cpp)

target_link_libraries(wasm.mjs math)
target_link_libraries(wasm.mjs util)
target_link_libraries(wasm.mjs engine)

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