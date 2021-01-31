#include "descriptor.h"

Descriptor::Descriptor() {
	_pool = new DescriptorPool();
	_layout = new DescriptorLayout();
	this->setup();
}

VkDescriptorSetLayout Descriptor::getLayout() {
	return this->_layout->getLayout();
}

VkDescriptorSet& Descriptor::getDescriptorSet(int _index) {
	return this->_descriptorSets[_index];
}

void Descriptor::setup() {
	int swapChainImageSize = SwapChainHandler::getInstance()->getSwapChainImagesSize();

	std::vector<VkDescriptorSetLayout> layouts(swapChainImageSize, _layout->getLayout());

	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = _pool->getPool();
	allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImageSize);
	allocInfo.pSetLayouts = layouts.data();

	_descriptorSets.resize(swapChainImageSize);
	if (vkAllocateDescriptorSets(DeviceHandler::getInstance()->getLogicalDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}
}

Descriptor::~Descriptor() {
	delete _pool;
	delete _layout;
}
