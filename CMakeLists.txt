option(BUILD_START "build the start directory" ON)
option(BUILD_DEMO "build the demo directory" ON)

cmake_minimum_required(VERSION 3.14)
project(PADEngine)

set(CMAKE_CXX_STANDARD 20)

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

find_package(Vulkan REQUIRED)
include_directories(
	external/glfw-3.3.2/include
	external/glm-0.9.9.8/glm
	external/tiny_obj_loader
	external/stb-images-2.26
)

set(ALL_LIBS
  Vulkan::Vulkan
  glfw
  glm
)

add_library(PADEngine STATIC
  project/source/main.cpp

  # PADEngine core engine files
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
  project/source/renderer.cpp
  project/source/renderer.h
  project/source/renderfactory.h
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
  project/source/storagebuffer.cpp
  project/source/storagebuffer.h
  project/source/imagebuffer.cpp
  project/source/imagebuffer.h
  project/source/texturebuffer.cpp
  project/source/texturebuffer.h
  project/source/depthbuffer.cpp
  project/source/depthbuffer.h
  project/source/samplingbuffer.cpp
  project/source/samplingbuffer.h
  project/source/framebuffers.cpp
  project/source/framebuffers.h
  project/source/meshbuffer.cpp
  project/source/meshbuffer.h
  project/source/modelloader.cpp
  project/source/modelloader.h

  # PADEngine shader files
  project/source/shadermanager.cpp
  project/source/shadermanager.h
  project/source/shaderstage.cpp
  project/source/shaderstage.h
  project/source/shadereffect.cpp
  project/source/shadereffect.h
  project/source/shaderpass.cpp
  project/source/shaderpass.h
  project/source/renderpass.cpp
  project/source/renderpass.h

  # PadEngine material files
  project/source/material.cpp
  project/source/material.h
  project/source/materialmanager.cpp
  project/source/materialmanager.h

  # PADEgine engine logic files
  project/source/scene.cpp
  project/source/scene.h
  project/source/mesh.cpp
  project/source/mesh.h
  project/source/texture.cpp
  project/source/texture.h
  project/source/entity.cpp
  project/source/entity.h
  project/source/vector3.cpp
  project/source/vector3.h
  project/source/vertex.h
  project/source/hierarchy.cpp
  project/source/hierarchy.h
  project/source/entity.cpp
  project/source/entity.h
  project/source/input.h
  project/source/input.cpp
  project/source/time.h
  project/source/time.cpp
  project/source/camera.h
  project/source/camera.cpp
  project/source/logger.h
)

target_include_directories(PADEngine PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(PADEngine
	${ALL_LIBS}
)

include_directories(
	project/source
)

if(BUILD_START)
  add_executable(PADEngine_startup
    startup/main.cpp
    startup/myscene.cpp
    startup/myscene.h
  )

  target_link_libraries(PADEngine_startup
    PADEngine
  )

  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PADEngine_startup)
endif(BUILD_START)
