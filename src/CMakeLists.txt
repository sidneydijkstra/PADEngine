
add_library(PADEngine STATIC
  # PADEngine core engine files
  config.h
  core.cpp
  core.h
  vulkanhandler.cpp
  vulkanhandler.h
  devicehandler.cpp
  devicehandler.h
  swapchainhandler.cpp
  swapchainhandler.h
  resourcemanager.cpp
  resourcemanager.h
  sequencemanager.cpp
  sequencemanager.h
  scenemanager.cpp
  scenemanager.h
  renderer.cpp
  renderer.h
  renderfactory.h
  descriptor.cpp
  descriptor.h
  descriptorpool.cpp
  descriptorpool.h
  descriptorlayout.cpp
  descriptorlayout.h
  buffer.cpp
  buffer.h
  vertexbuffer.cpp
  vertexbuffer.h
  indexbuffer.cpp
  indexbuffer.h
  uniformbuffer.h
  imagebuffer.cpp
  imagebuffer.h
  texturebuffer.cpp
  texturebuffer.h
  depthbuffer.cpp
  depthbuffer.h
  samplingbuffer.cpp
  samplingbuffer.h
  framebuffers.cpp
  framebuffers.h
  meshbuffer.cpp
  meshbuffer.h
  modelloader.cpp
  modelloader.h
  vertex.h

  # PADEngine shader files
  shadermanager.cpp
  shadermanager.h
  shaderstage.cpp
  shaderstage.h
  shadereffect.cpp
  shadereffect.h
  shaderpass.cpp
  shaderpass.h
  renderpass.cpp
  renderpass.h

  # PadEngine material files
  materialbuffer.cpp
  materialbuffer.h
  materialmanager.cpp
  materialmanager.h

  # PADEgine engine logic files
  scene.cpp
  scene.h
  mesh.cpp
  mesh.h
  texture.cpp
  texture.h
  entity.cpp
  entity.h
  vector3.h
  color.h
  hierarchy.cpp
  hierarchy.h
  entity.cpp
  entity.h
  light.cpp
  light.h
  material.cpp
  material.h
  input.h
  input.cpp
  time.h
  time.cpp
  camera.h
  camera.cpp
  logger.h
)

find_package(Vulkan REQUIRED)

target_include_directories(PADEngine PUBLIC ${Vulkan_INCLUDE_DIRS})

target_include_directories(PADEngine PUBLIC
    ${PADEngine_SOURCE_DIR}/external/glfw-3.3.2/include
    ${PADEngine_SOURCE_DIR}/external/glm-0.9.9.8/glm
    ${PADEngine_SOURCE_DIR}/external/tiny_obj_loader
    ${PADEngine_SOURCE_DIR}/external/stb-images-2.26
    ${PADEngine_SOURCE_DIR}/external/freetype-2.10.4/include
)

target_link_libraries(PADEngine
    Vulkan::Vulkan
    glfw
    glm
    freetype
)

set_property(DIRECTORY ${PADEngine_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PADEngine)
