#include "descriptorlayout.h"

DescriptorLayout::DescriptorLayout() {
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

	VkDescriptorSetLayoutBinding colorLayoutBinding{};
	colorLayoutBinding.binding = 2;
	colorLayoutBinding.descriptorCount = 1;
	colorLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	colorLayoutBinding.pImmutableSamplers = nullptr;
	colorLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	VkDescriptorSetLayoutBinding lightLayoutBinding{};
	lightLayoutBinding.binding = 3;
	lightLayoutBinding.descriptorCount = 1;
	lightLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	lightLayoutBinding.pImmutableSamplers = nullptr;
	lightLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	std::array<VkDescriptorSetLayoutBinding, 4> bindings = { uboLayoutBinding, samplerLayoutBinding, colorLayoutBinding, lightLayoutBinding };

	this->setup(bindings.size(), bindings.data());
}

DescriptorLayout::DescriptorLayout(VkDescriptorSetLayoutBinding _layoutBinding){
	this->setup(1, &_layoutBinding);
}

VkDescriptorSetLayout& DescriptorLayout::getLayout() {
	return this->_layout;
}

void DescriptorLayout::setup(int _size, VkDescriptorSetLayoutBinding* _layoutBinding) {
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(_size);
	layoutInfo.pBindings = _layoutBinding;

	if (vkCreateDescriptorSetLayout(DeviceHandler::getInstance()->getLogicalDevice(), &layoutInfo, nullptr, &_layout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

DescriptorLayout::~DescriptorLayout() {
	vkDestroyDescriptorSetLayout(DeviceHandler::getInstance()->getLogicalDevice(), _layout, nullptr);
}
