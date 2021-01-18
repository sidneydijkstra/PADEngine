
#ifndef VERTEXBUFFER_CLASS
#define VERTEXBUFFER_CLASS

#include "buffer.h"
#include "vertex.h"

#include <iostream>
#include <vector>
#include <string>

class VertexBuffer : Buffer {
public:
	VertexBuffer(const std::vector<Vertex> _vertices);
	~VertexBuffer();

	BufferData getBuffer();

private:
	VkBuffer _vertexBuffer;
	VkDeviceMemory _vertexBufferMemory;
	uint32_t _vertexSize;

	void setupBuffer(const std::vector<Vertex> _vertices);

};
#endif