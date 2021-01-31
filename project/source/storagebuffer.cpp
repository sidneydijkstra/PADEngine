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

void StorageBuffer::updateDescriptor(int _index, VkDescriptorSet _descriptor, int _dstBinding) {
    VkDescriptorBufferInfo colorInfo{};
    colorInfo.buffer = this->_buffers[_index];
    colorInfo.offset = 0;
    colorInfo.range = sizeof(StorageBufferData);

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