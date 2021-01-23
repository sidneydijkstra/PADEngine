cmake_minimum_required(VERSION 3.14)
project(PADEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(PAD_ENGINE_BUILD_EXAMPLES "Build PADEngine example programs." ON)

add_subdirectory(external/glfw-3.3.2)
add_subdirectory(external/glm-0.9.9.8)

include_directories(
    external/glfw-3.3.2/include
    external/glm-0.9.9.8/glm
    external/tiny_obj_loader
    external/stb-images-2.26
)

add_subdirectory(src)

if (PAD_ENGINE_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

