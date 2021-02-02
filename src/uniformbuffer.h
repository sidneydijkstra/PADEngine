/// @file uniformbuffer.h
/// @brief Standalone header providing UniformBuffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef UNIFORMBUFFER_CLASS
#define UNIFORMBUFFER_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "buffer.h"
#include "swapchainhandler.h"

#include <array>
#include <iostream>
#include <vector>
#include <string>

/// @brief Struct describing a UniformBufferObject object, which stores uniform buffer data.
struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

/// @brief Class describing a UniformBuffer, which handles the buffer for a uniform.
class UniformBuffer : Buffer {
public:
	/// @brief The constructor for the UniformBuffer class.
	UniformBuffer();
	/// @brief The deconstructor for the UniformBuffer class.
	~UniformBuffer();

	/// @brief Setup the buffer.
	void setupBuffer();

	/// @brief Update the buffer.
	/// @param _index Current index of SequenceManager.
	/// @param _ubo The UniformBufferObject to update the buffer with.
	void updateBuffer(int _index, UniformBufferObject _ubo);

	/// @brief Update descriptor set of buffer.
	/// @param _index Current index of SequenceManager.
	/// @return _descriptor VkDescriptorSet to use.
	/// @return _dstBinding Index to bind buffer to.
	void updateDescriptor(int _index, VkDescriptorSet _descriptor, int _dstBinding);

	/// @brief Recreate the buffer.
	void recreate();

private:
	std::vector<VkBuffer> _uniformBuffers; ///< @brief A std::vector of VkBuffer objects.
	std::vector<VkDeviceMemory> _uniformBuffersMemory; ///< @brief A std::vector of VkDeviceMemory objects.
};
#endif