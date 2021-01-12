
#ifndef VERTEXBUFFER_CLASS
#define VERTEXBUFFER_CLASS

#include "buffer.h"
#include "vertex.h"

#include <iostream>
#include <vector>
#include <string>

class VertexBuffer : Buffer {
public:
	VertexBuffer();
	~VertexBuffer();

	void setupBuffer();
	BufferData getBuffer();
	void recreate();

private:
	VkBuffer _vertexBuffer;
	VkDeviceMemory _vertexBufferMemory;

	const std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
		{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
	};

};
#endif