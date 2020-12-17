#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(VkInstance _instance, DeviceHandler* _deviceHandler, VkQueue _graphicsQueue, VkCommandPool _commandPool) :
Buffer(_instance, _deviceHandler, _graphicsQueue, _commandPool){
    this->setupBuffer();
}

void VertexBuffer::setupBuffer() {
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory);

    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _vertexBuffer, _vertexBufferMemory);
    this->copyBuffer(stagingBuffer, _vertexBuffer, bufferSize);

    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), stagingBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory, nullptr);
}

BufferData VertexBuffer::getBuffer() {
    return BufferData{ this->_vertexBuffer, (uint32_t)this->vertices.size() };
}

void VertexBuffer::recreate() {
    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _vertexBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _vertexBufferMemory, nullptr);

    this->setupBuffer();
}

VertexBuffer::~VertexBuffer() {
    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _vertexBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _vertexBufferMemory, nullptr);
}