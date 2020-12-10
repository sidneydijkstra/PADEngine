#include <cstdint>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "devicehandler.h"
#include "swapchainhandler.h"
#include "shader.h"
#include "vertex.h"

#include <iostream>
#include <array>
#include <vector>

#ifndef RENDERER_CLASS
#define RENDERER_CLASS

class Renderer {
public:
	Renderer(VkInstance _instance, DeviceHandler* _deviceHandler, SwapChainHandler* _swapChainHandler);
	~Renderer();

	void draw();
private:
	VkInstance _instance;
	DeviceHandler* _deviceHandler;
	SwapChainHandler* _swapChainHandler;
	Shader* _shader;

	VkCommandPool _commandPool;
	std::vector<VkCommandBuffer> _commandBuffers;

	VkQueue _graphicsQueue;
	VkQueue _presentQueue;

	VkBuffer _vertexBuffer;
	VkDeviceMemory _vertexBufferMemory;

	const std::vector<Vertex> vertices = {
		{{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
		{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
	};


	std::vector<VkSemaphore> _imageAvailableSemaphores;
	std::vector<VkSemaphore> _renderFinishedSemaphores;
	std::vector<VkFence> _inFlightFences;
	std::vector<VkFence> _imagesInFlight;
	size_t _currentFrame = 0;

	void setupCommandPool();
	void setupCommandBuffers();
	void setupSyncObjects();

	void setupBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void setupVertexBuffer();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	const int MAX_FRAMES_IN_FLIGHT = 2;
};
#endif