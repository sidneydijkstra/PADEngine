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
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "buffer.h"
#include "swapchainhandler.h"

#include <array>
#include <iostream>
#include <vector>
#include <string>

/// @brief Struct describing a UBOBufferObject object, which stores UBO buffer data.
struct UBOBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

/// @brief Struct describing a MaterialBufferObject object, which stores Material buffer data.
struct MaterialBufferObject {
    __declspec(align(16)) glm::vec3 color;
    __declspec(align(16)) glm::vec3 ambient;
    __declspec(align(16)) glm::vec3 diffuse;
    __declspec(align(16)) glm::vec3 specular;
    float shininess;
};

/// @brief Struct describing a MaterialBufferObject object, which stores Light buffer data.
struct LightBufferObject {
    __declspec(align(16)) glm::vec3 position;
    __declspec(align(16)) glm::vec3 cameraPosition;
    __declspec(align(16)) glm::vec3 color;
};

/// @brief Class describing a UniformBuffer, which handles the buffer for a uniform.
///
/// The UniformBuffer is a template class that takes a struct with data as a template T, which in turn is placed in memory using the Buffer functionality by extending from the Buffer. 
/// This is used to place the data like colorand position in memory in a specific way, so it can be sent to the Shader.
/// The buffers created for this data are kept up in a list that has the length of the SwapChainHandler its image size.
/// This is necessary because Vulkan supports calculating the next frame, while the current frame is still being rendered on the GPU.
/// If this data is changed during the rendering process, there will be errorsand this is why it is both requiredand preferred.

template <class T>
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
	/// @param _uniformBuffer The T data-type to update the buffer with.
	void updateBuffer(int _index, T _uniformBuffer);

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

template <class T>
UniformBuffer<T>::UniformBuffer() :
    Buffer() {
    this->setupBuffer();
}

template <class T>
void UniformBuffer<T>::setupBuffer() {
    VkDeviceSize bufferSize = sizeof(T);

    _uniformBuffers.resize(SwapChainHandler::getInstance()->getSwapChainImagesSize());
    _uniformBuffersMemory.resize(SwapChainHandler::getInstance()->getSwapChainImagesSize());

    for (size_t i = 0; i < SwapChainHandler::getInstance()->getSwapChainImagesSize(); i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
    }
}

template <class T>
void UniformBuffer<T>::updateBuffer(int _index, T _uniformBuffer) {
    void* data;
    vkMapMemory(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffersMemory[_index], 0, sizeof(_uniformBuffer), 0, &data);
    memcpy(data, &_uniformBuffer, sizeof(_uniformBuffer));
    vkUnmapMemory(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffersMemory[_index]);
}

template <class T>
void UniformBuffer<T>::updateDescriptor(int _index, VkDescriptorSet _descriptor, int _dstBinding) {
    VkDescriptorBufferInfo colorInfo{};
    colorInfo.buffer = this->_uniformBuffers[_index];
    colorInfo.offset = 0;
    colorInfo.range = sizeof(T);

    VkWriteDescriptorSet descriptorWrites{};

    descriptorWrites.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites.dstSet = _descriptor;
    descriptorWrites.dstBinding = _dstBinding;
    descriptorWrites.dstArrayElement = 0;
    descriptorWrites.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrites.descriptorCount = 1;
    descriptorWrites.pBufferInfo = &colorInfo;

    vkUpdateDescriptorSets(DeviceHandler::getInstance()->getLogicalDevice(), static_cast<uint32_t>(1), &descriptorWrites, 0, nullptr);
}

template <class T>
void UniformBuffer<T>::recreate() {
    for (size_t i = 0; i < _uniformBuffersMemory.size(); i++) {
        vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffersMemory[i], nullptr);
    }

    this->setupBuffer();
}

template <class T>
UniformBuffer<T>::~UniformBuffer() {
    for (size_t i = 0; i < _uniformBuffersMemory.size(); i++) {
        vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffersMemory[i], nullptr);
    }
}

#endif