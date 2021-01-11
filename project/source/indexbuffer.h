
#ifndef INDEXBUFFER_CLASS
#define INDEXBUFFER_CLASS

#include "buffer.h"

#include <iostream>
#include <vector>
#include <string>

class IndexBuffer : Buffer {
public:
	IndexBuffer(VkInstance _instance, VkCommandPool _commandPool);
	~IndexBuffer();

	void setupBuffer();
	BufferData getBuffer();
	void recreate();

private:
	VkBuffer _indexBuffer;
	VkDeviceMemory _indexBufferMemory;

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
	};
};
#endif