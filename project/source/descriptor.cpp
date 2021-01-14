#include "descriptor.h"

Descriptor::Descriptor() {
	this->setupDescriptorLayout();
	//this->setupDescriptorPool();
}

VkDescriptorSetLayout Descriptor::getLayout() {
	return this->_descriptorSetLayout;
}

VkDescriptorPool Descriptor::getPool() {
	VkDescriptorPool pool = this->setupDescriptorPool();
	_descriptorPools.push_back(pool);
	return pool;
}

void Descriptor::freePool(VkDescriptorPool _pool) {
	for (std::vector<VkDescriptorPool>::iterator it = _descriptorPools.begin(); it != _descriptorPools.end(); ++it){
		if (*it == _pool) {
			it = _descriptorPools.erase(it);
			vkDestroyDescriptorPool(DeviceHandler::getInstance()->getLogicalDevice(), _pool, nullptr);
		}

		if (_descriptorPools.empty())
			return;
	}
}

void Descriptor::setupDescriptorLayout() {
	VkDescriptorSetLayoutBinding uboLayoutBinding{};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.pImmutableSamplers = nullptr;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutBinding samplerLayoutBinding{};
	samplerLayoutBinding.binding = 1;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.pImmutableSamplers = nullptr;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
	layoutInfo.pBindings = bindings.data();

	if (vkCreateDescriptorSetLayout(DeviceHandler::getInstance()->getLogicalDevice(), &layoutInfo, nullptr, &_descriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

VkDescriptorPool Descriptor::setupDescriptorPool() {
	int swapChainImageSize = SwapChainHandler::getInstance()->getSwapChainImagesSize();

	std::array<VkDescriptorPoolSize, 2> poolSizes{};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImageSize);
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImageSize);

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(swapChainImageSize);

	VkDescriptorPool descriptorPool;
	if (vkCreateDescriptorPool(DeviceHandler::getInstance()->getLogicalDevice(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}

	return descriptorPool;
}

Descriptor::~Descriptor() {
	vkDestroyDescriptorSetLayout(DeviceHandler::getInstance()->getLogicalDevice(), _descriptorSetLayout, nullptr);
}
