#include "buffer.h"

Buffer::Buffer(VkInstance _instance, DeviceHandler* _deviceHandler, Shader* _shader, VkQueue _graphicsQueue, VkCommandPool _commandPool, int _swapChainImageSize) {
    this->_instance = _instance;
    this->_deviceHandler = _deviceHandler;
    this->_shader = _shader;

    this->_graphicsQueue = _graphicsQueue;
    this->_commandPool = _commandPool;
    this->_swapChainImageSize = _swapChainImageSize;

    this->setupVertexBuffer();
    this->setupIndexBuffer();
    this->setupUniformBuffers();
    this->setupDescriptorPool();
    this->setupDescriptorSets();
}

void Buffer::setupVertexBuffer() { // TODO: new
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

void Buffer::setupIndexBuffer() { // TODO: new
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

void Buffer::setupUniformBuffers() {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    _uniformBuffers.resize(_swapChainImageSize);
    _uniformBuffersMemory.resize(_swapChainImageSize);

    for (size_t i = 0; i < _swapChainImageSize; i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _uniformBuffers[i], _uniformBuffersMemory[i]);
    }
}

void Buffer::setupDescriptorPool() {
    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = static_cast<uint32_t>(_swapChainImageSize);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = static_cast<uint32_t>(_swapChainImageSize);

    if (vkCreateDescriptorPool(this->_deviceHandler->getLogicalDevice(), &poolInfo, nullptr, &_descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void Buffer::setupDescriptorSets() {
    std::vector<VkDescriptorSetLayout> layouts(_swapChainImageSize, this->_shader->getDescriptionSetLayout());
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = _descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(_swapChainImageSize);
    allocInfo.pSetLayouts = layouts.data();

    _descriptorSets.resize(_swapChainImageSize);
    if (vkAllocateDescriptorSets(this->_deviceHandler->getLogicalDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < _swapChainImageSize; i++) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = _uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = _descriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;
        descriptorWrite.pImageInfo = nullptr; // Optional
        descriptorWrite.pTexelBufferView = nullptr; // Optional
        vkUpdateDescriptorSets(this->_deviceHandler->getLogicalDevice(), 1, &descriptorWrite, 0, nullptr);
    }
}

void Buffer::updateUniformBuffers(int _index, UniformBufferObject _ubo) { // new and wierd
    void* data;
    vkMapMemory(this->_deviceHandler->getLogicalDevice(), _uniformBuffersMemory[_index], 0, sizeof(_ubo), 0, &data);
    memcpy(data, &_ubo, sizeof(_ubo));
    vkUnmapMemory(this->_deviceHandler->getLogicalDevice(), _uniformBuffersMemory[_index]);
}

BufferData Buffer::getVertexBuffer() {
    return BufferData { this->_vertexBuffer, (uint32_t)this->vertices.size() };
}

BufferData Buffer::getIndexBuffer() {
    return BufferData { this->_indexBuffer, (uint32_t)this->indices.size() };
}

std::vector<VkDescriptorSet> Buffer::getDescriptorSets() {
    return this->_descriptorSets;
}

void Buffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) { // TODO: new
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(this->_deviceHandler->getLogicalDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(this->_deviceHandler->getLogicalDevice(), buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(this->_deviceHandler->getLogicalDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(this->_deviceHandler->getLogicalDevice(), buffer, bufferMemory, 0);
}

uint32_t Buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) { // TODO: new
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(this->_deviceHandler->getPhysicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void Buffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){ // TODO: new
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = _commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(this->_deviceHandler->getLogicalDevice(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0; // Optional
    copyRegion.dstOffset = 0; // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(_graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(_graphicsQueue);

    vkFreeCommandBuffers(this->_deviceHandler->getLogicalDevice(), _commandPool, 1, &commandBuffer);
}

Buffer::~Buffer() {
    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _indexBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _indexBufferMemory, nullptr);

    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _vertexBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _vertexBufferMemory, nullptr);

    for (size_t i = 0; i < _uniformBuffersMemory.size(); i++) {
        vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _uniformBuffers[i], nullptr);
        vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _uniformBuffersMemory[i], nullptr);
    }

    vkDestroyDescriptorPool(this->_deviceHandler->getLogicalDevice(), _descriptorPool, nullptr);
}
