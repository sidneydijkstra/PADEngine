cmake_minimum_required(VERSION 3.14)
project(PADEngine)


set(CMAKE_CXX_STANDARD 20)


add_executable(PADEngine
  project/source/main.cpp
  project/source/config.h
  project/source/core.cpp
  project/source/core.h
  project/source/vulkanhandler.cpp
  project/source/vulkanhandler.h
  project/source/devicehandler.cpp
  project/source/devicehandler.h
  project/source/swapchainhandler.cpp
  project/source/swapchainhandler.h
  project/source/resourcemanager.cpp
  project/source/resourcemanager.h
  project/source/sequencemanager.cpp
  project/source/sequencemanager.h
  project/source/shader.cpp
  project/source/shader.h
  project/source/renderer.cpp
  project/source/renderer.h
  project/source/descriptor.cpp
  project/source/descriptor.h
  project/source/buffer.cpp
  project/source/buffer.h
  project/source/vertexbuffer.cpp
  project/source/vertexbuffer.h
  project/source/indexbuffer.cpp
  project/source/indexbuffer.h
  project/source/uniformbuffer.cpp
  project/source/uniformbuffer.h
  project/source/texturebuffer.cpp
  project/source/texturebuffer.h
  project/source/depthbuffer.cpp
  project/source/depthbuffer.h
  project/source/framebuffers.cpp
  project/source/framebuffers.h
  project/source/scene.cpp
  project/source/scene.h
  project/source/texture.cpp
  project/source/texture.h
  project/source/entity.cpp
  project/source/entity.h
  project/source/vector3.cpp
  project/source/vector3.h
  project/source/vertex.h
  project/source/stb_image.h
  project/source/input.h
  project/source/input.cpp
  project/source/time.h
  project/source/time.cpp
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
)
find_package(Vulkan REQUIRED)
target_include_directories(PADEngine PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(PADEngine
  Vulkan::Vulkan
  glfw
  glm
)
