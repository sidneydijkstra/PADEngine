#include "entity.h"

Entity::Entity() : Hierarchy() {
	rotation = Vector3(0, 0, 0);
	position = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
	color = Color();
	
    _mesh = new Mesh();
	_mesh->loadShape(MeshType::CUBE);
	_colorBuffer = new StorageBuffer();
    _uniformBuffer = new UniformBuffer();

    _texture = new Texture();
	_material = MaterialManager::getInstance()->get("mat_normal_PBR");

	this->setupDescriptorSets();
}

UniformBuffer* Entity::getUniformBuffer() {
	return this->_uniformBuffer;
}

StorageBuffer* Entity::getColorBuffer() {
	return this->_colorBuffer;
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

VkDescriptorSet& Entity::getDescriptorSet(int _index) {
	return this->_descriptorSets[_index];
}

void Entity::recreate(int _index) {
}

void Entity::updateDescriptors(int _index) {
	this->_uniformBuffer->updateDescriptor(_index, _descriptorSets[_index], 0);
	this->_texture->getBuffer()->updateDescriptor(_index, _descriptorSets[_index], 1);
	this->_colorBuffer->updateDescriptor(_index, _descriptorSets[_index], 2);
}

void Entity::setupDescriptorSets() {
	int swapChainImageSize = SwapChainHandler::getInstance()->getSwapChainImagesSize();
	_pool = this->_material->getDescriptor()->getPool();

	std::vector<VkDescriptorSetLayout> layouts(swapChainImageSize, _material->getDescriptor()->getLayout());

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

Entity::~Entity() {
	delete _mesh;
	delete _uniformBuffer;
	delete _colorBuffer;
	delete _texture;

	this->_material->getDescriptor()->freePool(_pool);
}
