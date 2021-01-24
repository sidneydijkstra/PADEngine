
SET(PADEngine_DOXYGEN_SOURCES
    "src/mesh.h"
    "src/materialmanager.h"
    "src/meshbuffer.h"
    "src/material.h"
    "src/modelloader.h"
    "src/logger.h"
    "src/renderer.h"
    "src/renderfactory.h"
    "src/input.h"
    "src/renderpass.h"
    "src/indexbuffer.h"
    "src/resourcemanager.h"
    "src/imagebuffer.h"
    "src/samplingbuffer.h"
    "src/hierarchy.h"
    "src/scene.h"
    "src/framebuffers.h"
    "src/sequencemanager.h"
    "src/shadereffect.h"
    "src/entity.h"
    "src/shadermanager.h"
    "src/devicehandler.h"
    "src/shaderpass.h"
    "src/descriptor.h"
    "src/shaderstage.h"
    "src/depthbuffer.h"
    "src/swapchainhandler.h"
    "src/core.h"
    "src/texture.h"
    "src/config.h"
    "src/texturebuffer.h"
    "src/time.h"
    "src/vertexbuffer.h"
    "src/uniformbuffer.h"
    "src/camera.h"
    "src/vector3.h"
    "src/vertex.h"
    "src/buffer.h"
    "src/vulkanhandler.h"
)

foreach(path IN LISTS PADEngine_DOXYGEN_SOURCES)
    set(PADEngine_DOXYGEN_INPUT "${PADEngine_DOXYGEN_INPUT} \\\n\"${PADEngine_SOURCE_DIR}/${path}\"")
endforeach()

configure_file(Doxyfile.in Doxyfile @ONLY)

add_custom_target(docs ALL "${DOXYGEN_EXECUTABLE}"
                  WORKING_DIRECTORY "${PADEngine_BINARY_DIR}/docs"
                  COMMENT "Generating documentation" VERBATIM)