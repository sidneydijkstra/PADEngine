/// @file buffer.h
/// @brief Standalone header providing Buffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef BUFFER_CLASS
#define BUFFER_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLM_DEPTH_ZERO_TO_ONE
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "vulkanhandler.h"
#include "devicehandler.h"

#include <iostream>
#include <vector>
#include <string>

//namespace pad {

/// @brief Struct describing a Buffer data object, which stores VkBuffer and buffer size.
struct BufferData {
	VkBuffer buffer;
	uint32_t size;
};

/// @brief Class describing a Buffer object, which is used to store variables in vulkan buffer objects.
///
/// The Buffer class is an abstract class that contains the functionality to create a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkBuffer.html">VkBuffer</a> object. 
/// This object contains data that is sent to the Shader which is rendered by the GPU. 
/// The Buffer class can also start and close a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkCommandBuffer.html">VkCommandBuffer</a> to copy buffers. 
/// The <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkCommandBuffer.html">VkCommandBuffer</a> is used to place data or buffers on the right place in memory.

class Buffer {
public:
	/// @brief The deconstructor of the Buffer class.
	virtual ~Buffer();

protected:
	/// @brief The constructor of the Buffer class.
	Buffer();
	/// @brief The copy constructor of the Buffer class.
	Buffer(const Buffer& _other) = default;
	/// @brief The move constructor of the Buffer class.
	Buffer(Buffer&& _other) = default;

	/// @brief Begin a single time Buffer command.
    /// @return A reference to the command buffer.
	VkCommandBuffer beginSingleTimeCommands();

	/// @brief End a single time Buffer command.
	/// @param commandBuffer A reference to the command buffer.
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	/// @brief Create a new Buffer to store data.
	/// @param size The size for the Buffer.
	/// @param usage The usage for the Buffer.
	/// @param properties The memory property's for the Buffer.
	/// @param Buffer The buffer reference fo VkBuffer.
	/// @param bufferMemory The buffer memory reference fo VkDeviceMemory.
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	/// @brief Copy a buffer's data to an diffrent buffer.
	/// @param srcBuffer The buffer to copy from.
	/// @param dstBuffer The buffer to copy to.
	/// @param size The size for the Buffer.
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	/// @brief Find the right memory type with the correct properties
	/// @param typeFilter The memory type filter.
	/// @param properties The memory properties.
	/// @return The memory type.
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

};

//}
#endif