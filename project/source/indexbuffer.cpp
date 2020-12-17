#include "indexbuffer.h"

IndexBuffer::IndexBuffer(VkInstance _instance, DeviceHandler* _deviceHandler, VkQueue _graphicsQueue, VkCommandPool _commandPool) :
    Buffer(_instance, _deviceHandler, _graphicsQueue, _commandPool) {
    this->setupBuffer();
}


void IndexBuffer::setupBuffer() {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory);

    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _indexBuffer, _indexBufferMemory);

    copyBuffer(stagingBuffer, _indexBuffer, bufferSize);

    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), stagingBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory, nullptr);
}

BufferData IndexBuffer::getBuffer() {
    return BufferData{ this->_indexBuffer, (uint32_t)this->indices.size() };
}

void IndexBuffer::recreate() {
    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _indexBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _indexBufferMemory, nullptr);

    this->setupBuffer();
}

IndexBuffer::~IndexBuffer() {
    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _indexBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _indexBufferMemory, nullptr);
}