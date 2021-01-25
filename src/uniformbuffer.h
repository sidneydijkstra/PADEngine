
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <array>

#ifndef UNIFORMBUFFER_CLASS
#define UNIFORMBUFFER_CLASS

#include "buffer.h"
#include "swapchainhandler.h"

#include <iostream>
#include <vector>
#include <string>

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

struct UniformBufferData {
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
};

class UniformBuffer : Buffer {
public:
	UniformBuffer();
	~UniformBuffer();

	void setupBuffer();
	void updateBuffer(int _index, UniformBufferObject _ubo);
	UniformBufferData getBuffer();
	void recreate();

private:
	std::vector<VkBuffer> _uniformBuffers;
	std::vector<VkDeviceMemory> _uniformBuffersMemory;
};
#endif