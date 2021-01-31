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

void UniformBuffer::updateDescriptor(int _index, VkDescriptorSet _descriptor, int _dstBinding) {
    VkDescriptorBufferInfo colorInfo{};
    colorInfo.buffer = this->_uniformBuffers[_index];
    colorInfo.offset = 0;
    colorInfo.range = sizeof(UniformBufferData);

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
