#include "entity.h"

Entity::Entity() : Hierarchy() {
	rotation = Vector3(0, 0, 0);
	position = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
	
    _mesh = new Mesh();
	_mesh->loadShape(MeshType::CUBE);
    _uniformBuffer = new UniformBuffer();

    _texture = new Texture();
	_material = MaterialManager::getInstance()->get("mat_normal_PBR");

	this->setupDescriptorSets();
}

UniformBuffer* Entity::getUniform() {
	return this->_uniformBuffer;
}

Mesh* Entity::getMesh() {
	return this->_mesh;
}

Texture* Entity::getTexture() {
	return this->_texture;
}

Material* Entity::getMaterial() {
	return this->_material;
}

void Entity::setMaterial(const char* _name) {
	this->_material->getDescriptor()->freePool(_pool);
	this->_material = MaterialManager::getInstance()->get(_name);
	this->setupDescriptorSets();
}

std::vector<VkDescriptorSet> Entity::description() {
	return this->_descriptorSets;
}

void Entity::recreate(int _index) {
	this->updateDescriptorSets(_index);
}

void Entity::setupDescriptorSets() {
	int swapChainImageSize = SwapChainHandler::getInstance()->getSwapChainImagesSize();
	_pool = _material->getDescriptor()->getPool();

	std::vector<VkDescriptorSetLayout> layouts(swapChainImageSize, _material->getDescriptor()->getLayout());

	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = _pool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImageSize);
	allocInfo.pSetLayouts = layouts.data();

	_descriptorSets.resize(swapChainImageSize);
	if (vkAllocateDescriptorSets(DeviceHandler::getInstance()->getLogicalDevice(), &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < swapChainImageSize; i++) {
		this->updateDescriptorSets(i);
	}
}

void Entity::updateDescriptorSets(int _index) {
	int swapChainImageSize = SwapChainHandler::getInstance()->getSwapChainImagesSize();

	std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

	VkDescriptorBufferInfo bufferInfo{};
	bufferInfo.buffer = _uniformBuffer->getBuffer().uniformBuffers[_index];
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(UniformBufferObject);

	descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrites[0].dstSet = _descriptorSets[_index];
	descriptorWrites[0].dstBinding = 0;
	descriptorWrites[0].dstArrayElement = 0;
	descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrites[0].descriptorCount = 1;
	descriptorWrites[0].pBufferInfo = &bufferInfo;

	VkDescriptorImageInfo imageInfo{};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	imageInfo.imageView = _texture->getBuffer()->getImageView();
	imageInfo.sampler = _texture->getBuffer()->getSampler();

	descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrites[1].dstSet = _descriptorSets[_index];
	descriptorWrites[1].dstBinding = 1;
	descriptorWrites[1].dstArrayElement = 0;
	descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptorWrites[1].descriptorCount = 1;
	descriptorWrites[1].pImageInfo = &imageInfo;

	vkUpdateDescriptorSets(DeviceHandler::getInstance()->getLogicalDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}

Entity::~Entity() {
	delete _mesh;
	delete _uniformBuffer;
	delete _texture;

	_material->getDescriptor()->freePool(_pool);
}
