cmake_minimum_required(VERSION 3.14)
project(PADEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(PADEngine_BUILD_EXAMPLES "Build PADEngine example programs." ON)
option(PADEngine_BUILD_DOCS "Build PADEngine documentation." ON)

#--------------------------------------------------------------------
# Build dependencies
#--------------------------------------------------------------------

# Disable unnecessary build options and prevent name clashes with PAD Engine's build targets.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.3.2)
add_subdirectory(external/glm-0.9.9.8)

#--------------------------------------------------------------------
# Build PAD Engine
#--------------------------------------------------------------------

add_subdirectory(src)

if(PADEngine_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(PADEngine_BUILD_DOCS)
    set(DOXYGEN_SKIP_DOT TRUE)
    find_package(Doxygen)

    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    else()
        message(WARNING "Doxygen not found! Could not build documentation.")
    endif()
endif()

