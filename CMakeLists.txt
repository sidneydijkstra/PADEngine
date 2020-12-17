cmake_minimum_required(VERSION 3.14)
project(PADEngine)


set(CMAKE_CXX_STANDARD 20)


add_executable(PADEngine
  project/source/main.cpp
  project/source/config.h
  project/source/core.cpp
  project/source/core.h
  project/source/devicehandler.cpp
  project/source/devicehandler.h
  project/source/swapchainhandler.cpp
  project/source/swapchainhandler.h
  project/source/shader.cpp
  project/source/shader.h
  project/source/renderer.cpp
  project/source/renderer.h
  project/source/buffer.cpp
  project/source/buffer.h
  project/source/vertex.h
  project/source/uniformbuffer.h
)

file(
	COPY project/assets
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY project/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)

add_subdirectory(external/glfw-3.3.2)
add_subdirectory(external/glm-0.9.9.8)

include_directories(
	external/glfw-3.3.2/include
	external/glm-0.9.9.8/glm
	external/stb-images-2.26
)

find_package(Vulkan REQUIRED)
target_include_directories(PADEngine PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(PADEngine
  Vulkan::Vulkan
  glfw
  glm
)
