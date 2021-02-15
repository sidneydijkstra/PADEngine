#include "descriptorpool.h"

namespace pad {

DescriptorPool::DescriptorPool() {
	int swapChainImageSize = SwapChainHandler::getInstance()->getSwapChainImagesSize();

	std::array<VkDescriptorPoolSize, 4> poolSizes{};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImageSize);
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImageSize);
	poolSizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[2].descriptorCount = static_cast<uint32_t>(swapChainImageSize);
	poolSizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[2].descriptorCount = static_cast<uint32_t>(swapChainImageSize);
	poolSizes[3].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[3].descriptorCount = static_cast<uint32_t>(swapChainImageSize);

	this->setup(poolSizes.size(), poolSizes.data());
}

DescriptorPool::DescriptorPool(VkDescriptorPoolSize _poolSize) {
	this->setup(1, &_poolSize);
}

DescriptorPool::DescriptorPool(int _size, const VkDescriptorPoolSize* _poolSizeData) {
	this->setup(_size, _poolSizeData);
}

VkDescriptorPool& DescriptorPool::getPool() {
	return this->_pool;
}

void DescriptorPool::setup(int _size, const VkDescriptorPoolSize* _poolSizeData) {
	int swapChainImageSize = SwapChainHandler::getInstance()->getSwapChainImagesSize();

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(_size);
	poolInfo.pPoolSizes = _poolSizeData;
	poolInfo.maxSets = static_cast<uint32_t>(swapChainImageSize);

	if (vkCreateDescriptorPool(DeviceHandler::getInstance()->getLogicalDevice(), &poolInfo, nullptr, &_pool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

DescriptorPool::~DescriptorPool() {
	vkDestroyDescriptorPool(DeviceHandler::getInstance()->getLogicalDevice(), _pool, nullptr);
}

}