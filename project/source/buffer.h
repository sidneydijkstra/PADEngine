
#ifndef BUFFER_CLASS
#define BUFFER_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "devicehandler.h"

#include <iostream>
#include <vector>
#include <string>

struct BufferData {
	VkBuffer buffer;
	uint32_t size;
};

class Buffer {
public:
	Buffer(VkInstance _instance, VkQueue _graphicsQueue, VkCommandPool _commandPool);
	~Buffer();

protected:
	VkInstance _instance;

	VkQueue _graphicsQueue;
	VkCommandPool _commandPool;

	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};
#endif