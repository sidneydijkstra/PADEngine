glslc vertex_shader.vert -o vert.spv
glslc fragment_shader.frag -o frag.spv
cd ../../build
cmake ..
PAUSE
