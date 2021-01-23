
link_libraries(PADEngine)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(PADEngine_startup
    startup/main.cpp
    startup/myscene.cpp
    startup/myscene.h
)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PADEngine_startup)
