
#ifndef STORAGEBUFFER_CLASS
#define STORAGEBUFFER_CLASS

#include "buffer.h"
#include "swapchainhandler.h"

struct StorageBufferData {
	glm::vec3 data;
};

template <class T>
class StorageBuffer : Buffer {
	public:
		StorageBuffer();
		~StorageBuffer();

		std::vector<VkBuffer> getBuffer();

		void updateBuffer(int _index, T _bufferData);
		void updateDescriptor(int _index, VkDescriptorSet _descriptor, int _dstBinding);
		void recreate();

	private:
		std::vector<VkBuffer> _buffers;
		std::vector<VkDeviceMemory> _buffersMemory;

		void setupBuffer();
};

template <class T>
StorageBuffer<T>::StorageBuffer() : Buffer() {
    this->setupBuffer();
}

template <class T>
std::vector<VkBuffer> StorageBuffer<T>::getBuffer() {
    return this->_buffers;
}

template <class T>
void StorageBuffer<T>::setupBuffer() {
    VkDeviceSize bufferSize = sizeof(T);

    _buffers.resize(SwapChainHandler::getInstance()->getSwapChainImagesSize());
    _buffersMemory.resize(SwapChainHandler::getInstance()->getSwapChainImagesSize());

    for (size_t i = 0; i < SwapChainHandler::getInstance()->getSwapChainImagesSize(); i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _buffers[i], _buffersMemory[i]);
    }
}

template <class T>
void StorageBuffer<T>::updateBuffer(int _index, T _bufferData) {
    void* data;
    vkMapMemory(DeviceHandler::getInstance()->getLogicalDevice(), _buffersMemory[_index], 0, sizeof(_bufferData), 0, &data);
    memcpy(data, &_bufferData, sizeof(_bufferData));
    vkUnmapMemory(DeviceHandler::getInstance()->getLogicalDevice(), _buffersMemory[_index]);
}

template <class T>
void StorageBuffer<T>::updateDescriptor(int _index, VkDescriptorSet _descriptor, int _dstBinding) {
    VkDescriptorBufferInfo colorInfo{};
    colorInfo.buffer = this->_buffers[_index];
    colorInfo.offset = 0;
    colorInfo.range = sizeof(T);

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

template <class T>
void StorageBuffer<T>::recreate() {
    for (size_t i = 0; i < _buffersMemory.size(); i++) {
        vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _buffers[i], nullptr);
        vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _buffersMemory[i], nullptr);
    }

    this->setupBuffer();
}

template <class T>
StorageBuffer<T>::~StorageBuffer() {
    for (size_t i = 0; i < _buffersMemory.size(); i++) {
        vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), _buffers[i], nullptr);
        vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _buffersMemory[i], nullptr);
    }
}

#endif


