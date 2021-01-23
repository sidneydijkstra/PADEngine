#include "uniformbuffer.h"

UniformBuffer::UniformBuffer() :
    Buffer() {
    this->setupBuffer();
}

void UniformBuffer::setupBuffer() {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    _uniformBuffers.resize(SwapChainHandler::getInstance()->getSwapChainImagesSize());
    _uniformBuffersMemory.resize(SwapChainHandler::getInstance()->getSwapChainImagesSize());

    for (size_t i = 0; i < SwapChainHandler::getInstance()->getSwapChainImagesSize(); i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
    }
}

void UniformBuffer::updateBuffer(int _index, UniformBufferObject _ubo) {
    void* data;
    vkMapMemory(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffersMemory[_index], 0, sizeof(_ubo), 0, &data);
    memcpy(data, &_ubo, sizeof(_ubo));
    vkUnmapMemory(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffersMemory[_index]);
}

UniformBufferData UniformBuffer::getBuffer() {
    return UniformBufferData{this->_uniformBuffers, this->_uniformBuffersMemory};
}

void UniformBuffer::recreate() {
    for (size_t i = 0; i < _uniformBuffersMemory.size(); i++) {
        vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffersMemory[i], nullptr);
    }

    this->setupBuffer();
}

UniformBuffer::~UniformBuffer() {
    for (size_t i = 0; i < _uniformBuffersMemory.size(); i++) {
        vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _uniformBuffersMemory[i], nullptr);
    }
}
