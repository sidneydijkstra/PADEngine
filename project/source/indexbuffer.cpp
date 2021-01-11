#include "indexbuffer.h"

IndexBuffer::IndexBuffer(VkInstance _instance, VkCommandPool _commandPool) :
    Buffer(_instance, _commandPool) {
    this->setupBuffer();
}


void IndexBuffer::setupBuffer() {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory);

    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _indexBuffer, _indexBufferMemory);

    copyBuffer(stagingBuffer, _indexBuffer, bufferSize);

    vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), stagingBuffer, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory, nullptr);
}

BufferData IndexBuffer::getBuffer() {
    return BufferData{ this->_indexBuffer, (uint32_t)this->indices.size() };
}

void IndexBuffer::recreate() {
    vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _indexBuffer, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _indexBufferMemory, nullptr);

    this->setupBuffer();
}

IndexBuffer::~IndexBuffer() {
    vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _indexBuffer, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _indexBufferMemory, nullptr);
}