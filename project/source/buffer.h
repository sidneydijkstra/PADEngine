
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
#include "shader.h"
#include "vertex.h"
#include "uniformbuffer.h"

#include <iostream>
#include <vector>
#include <string>

struct BufferData {
	VkBuffer buffer;
	uint32_t size;
};

class Buffer {
public:
	Buffer(VkInstance _instance, DeviceHandler* _deviceHandler, Shader* _shader, VkQueue _graphicsQueue, VkCommandPool _commandPool, int _swapChainImageSize);
	~Buffer();

	void setupVertexBuffer();
	void setupIndexBuffer();
	void setupUniformBuffers();
	void setupDescriptorPool();
	void setupDescriptorSets();

	void updateUniformBuffers(int _index, UniformBufferObject _ubo);

	BufferData getVertexBuffer();
	BufferData getIndexBuffer();
	std::vector<VkDescriptorSet> getDescriptorSets();

private:
	VkInstance _instance;
	DeviceHandler* _deviceHandler;
	Shader* _shader;

	VkQueue _graphicsQueue;
	VkCommandPool _commandPool;

	VkBuffer _vertexBuffer;
	VkDeviceMemory _vertexBufferMemory;

	VkBuffer _indexBuffer;
	VkDeviceMemory _indexBufferMemory;

	std::vector<VkBuffer> _uniformBuffers;
	std::vector<VkDeviceMemory> _uniformBuffersMemory;
	VkDescriptorPool _descriptorPool;
	std::vector<VkDescriptorSet> _descriptorSets;

	const std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
	};

	int _swapChainImageSize;

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};
#endif