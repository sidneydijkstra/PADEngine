#include "entity.h"

Entity::Entity() : Hierarchy() {
	rotation = Vector3(0, 0, 0);
	position = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
	
	_type = EntityType::ENTITY;

    _mesh = new Mesh();
	_mesh->loadShape(MeshType::CUBE);
    _uniformBuffer = new UniformBuffer<UBOBufferObject>();

    _texture = new Texture();
	_material = new Material();

	this->setupDescriptorSets();
}

UniformBuffer<UBOBufferObject>* Entity::getUniformBuffer() {
	return this->_uniformBuffer;
}

EntityType Entity::getType() {
	return this->_type;
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

VkDescriptorSet& Entity::getDescriptorSet(int _index) {
	return this->_descriptorSets[_index];
}

void Entity::update() {
}

void Entity::recreate(int _index) {
}

void Entity::updateDescriptors(int _index) {
	if(this->getType() != EntityType::CUSTOM){
		this->_uniformBuffer->updateDescriptor(_index, _descriptorSets[_index], 0);
		this->_texture->getBuffer()->updateDescriptor(_index, _descriptorSets[_index], 1);
		this->_material->updateDescriptors(_index, _descriptorSets[_index]);
	}
}

void Entity::setupDescriptorSets() {
	int swapChainImageSize = SwapChainHandler::getInstance()->getSwapChainImagesSize();

	std::vector<VkDescriptorSetLayout> layouts(swapChainImageSize, _material->getMaterialBuffer()->getDescriptor()->getLayout());

	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = this->_material->getPool();
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
	delete _texture;
	delete _material;
}
