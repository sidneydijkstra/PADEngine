#include "indexbuffer.h"

namespace pad {

IndexBuffer::IndexBuffer(std::vector<uint32_t> _indices) : Buffer() {
    this->_indexSize = (uint32_t)_indices.size();
    this->setupBuffer(_indices);
}


void IndexBuffer::setupBuffer(std::vector<uint32_t> _indices) {
    VkDeviceSize bufferSize = sizeof(_indices[0]) * _indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, _indices.data(), (size_t)bufferSize);
    vkUnmapMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory);

    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _indexBuffer, _indexBufferMemory);

    copyBuffer(stagingBuffer, _indexBuffer, bufferSize);

    vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), stagingBuffer, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory, nullptr);
}

VkBuffer IndexBuffer::getBuffer() {
    return this->_indexBuffer;
}

uint32_t IndexBuffer::getBufferSize() {
    return this->_indexSize;
}

IndexBuffer::~IndexBuffer() {
    vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _indexBuffer, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _indexBufferMemory, nullptr);
}

}