#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const std::vector<Vertex> _vertices) :
Buffer(){
    _vertexSize = (uint32_t)_vertices.size();
    this->setupBuffer(_vertices);
}

void VertexBuffer::setupBuffer(const std::vector<Vertex> _vertices) {
    VkDeviceSize bufferSize = sizeof(_vertices[0]) * _vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, _vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory);

    this->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _vertexBuffer, _vertexBufferMemory);
    this->copyBuffer(stagingBuffer, _vertexBuffer, bufferSize);

    vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), stagingBuffer, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory, nullptr);
}

BufferData VertexBuffer::getBuffer() {
    return BufferData{ this->_vertexBuffer, this->_vertexSize };
}

VertexBuffer::~VertexBuffer() {
    vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _vertexBuffer, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _vertexBufferMemory, nullptr);
}