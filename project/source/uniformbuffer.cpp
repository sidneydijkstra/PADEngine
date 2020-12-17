#include "uniformbuffer.h"

UniformBuffer::UniformBuffer(VkInstance _instance, DeviceHandler* _deviceHandler, VkQueue _graphicsQueue, VkCommandPool _commandPool, int _swapChainImageSize) :
    Buffer(_instance, _deviceHandler, _graphicsQueue, _commandPool) {
    this->_swapChainImageSize = _swapChainImageSize;
    this->setupBuffer();
}

void UniformBuffer::setupBuffer() {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    _uniformBuffers.resize(_swapChainImageSize);
    _uniformBuffersMemory.resize(_swapChainImageSize);

    for (size_t i = 0; i < _swapChainImageSize; i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
    }
}

void UniformBuffer::updateBuffer(int _index, UniformBufferObject _ubo) {
    void* data;
    vkMapMemory(this->_deviceHandler->getLogicalDevice(), _uniformBuffersMemory[_index], 0, sizeof(_ubo), 0, &data);
    memcpy(data, &_ubo, sizeof(_ubo));
    vkUnmapMemory(this->_deviceHandler->getLogicalDevice(), _uniformBuffersMemory[_index]);

}

UniformBufferData UniformBuffer::getBuffer() {
    return UniformBufferData{this->_uniformBuffers, this->_uniformBuffersMemory};
}

void UniformBuffer::recreate() {
    for (size_t i = 0; i < _uniformBuffersMemory.size(); i++) {
        vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _uniformBuffersMemory[i], nullptr);
    }

    this->setupBuffer();
}

UniformBuffer::~UniformBuffer() {
    for (size_t i = 0; i < _uniformBuffersMemory.size(); i++) {
        vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _uniformBuffersMemory[i], nullptr);
    }
}
