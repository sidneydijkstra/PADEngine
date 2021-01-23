
#ifndef INDEXBUFFER_CLASS
#define INDEXBUFFER_CLASS

#include "buffer.h"

#include <iostream>
#include <vector>
#include <string>

class IndexBuffer : Buffer {
public:
	IndexBuffer(std::vector<uint32_t> _indices);
	~IndexBuffer();

	BufferData getBuffer();

private:
	VkBuffer _indexBuffer;
	VkDeviceMemory _indexBufferMemory;
	uint32_t _indexSize;

	void setupBuffer(std::vector<uint32_t> _indices);
};
#endif