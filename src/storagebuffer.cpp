#include "storagebuffer.h"

StorageBuffer::StorageBuffer() : Buffer() {
    this->setupBuffer();
}

std::vector<VkBuffer> StorageBuffer::getBuffer() {
    return this->_buffers;
}

void StorageBuffer::setupBuffer() {
    VkDeviceSize bufferSize = sizeof(glm::vec3);

    _buffers.resize(SwapChainHandler::getInstance()->getSwapChainImagesSize());
    _buffersMemory.resize(SwapChainHandler::getInstance()->getSwapChainImagesSize());

    for (size_t i = 0; i < SwapChainHandler::getInstance()->getSwapChainImagesSize(); i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _buffers[i], _buffersMemory[i]);
    }
}

void StorageBuffer::updateBuffer(int _index, StorageBufferData _bufferData) {
    void* data;
    vkMapMemory(DeviceHandler::getInstance()->getLogicalDevice(), _buffersMemory[_index], 0, sizeof(_bufferData), 0, &data);
    memcpy(data, &_bufferData, sizeof(_bufferData));
    vkUnmapMemory(DeviceHandler::getInstance()->getLogicalDevice(), _buffersMemory[_index]);
}

void StorageBuffer::recreate() {
    for (size_t i = 0; i < _buffersMemory.size(); i++) {
        vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _buffers[i], nullptr);
        vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _buffersMemory[i], nullptr);
    }

    this->setupBuffer();
}

StorageBuffer::~StorageBuffer() {
    for (size_t i = 0; i < _buffersMemory.size(); i++) {
        vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _buffers[i], nullptr);
        vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _buffersMemory[i], nullptr);
    }
}