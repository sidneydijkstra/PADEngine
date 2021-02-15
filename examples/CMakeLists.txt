
file(
    COPY ${PADEngine_SOURCE_DIR}/examples/assets
    DESTINATION ${PADEngine_BINARY_DIR}/examples
)

file(
    COPY ${PADEngine_SOURCE_DIR}/examples/shaders
    DESTINATION ${PADEngine_BINARY_DIR}/examples
)

link_libraries(PADEngine)

include_directories(${PADEngine_SOURCE_DIR}/src)

add_executable(PADEngine_startup
    startup/main.cpp
    startup/myscene.cpp
    startup/myscene.h
)

add_executable(PADEngine_demo
    demo/main.cpp

    demo/collisiondemo/collisiondemo.cpp
    demo/collisiondemo/collisiondemo.h

    demo/lightdemo/lightdemo.cpp
    demo/lightdemo/lightdemo.h

    demo/shaderdemo/shaderdemo.cpp
    demo/shaderdemo/shaderdemo.h
    demo/shaderdemo/canvas.cpp
    demo/shaderdemo/canvas.h
)

set_property(DIRECTORY ${PADEngine_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PADEngine_startup)
