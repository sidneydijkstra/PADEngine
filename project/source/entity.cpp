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
	this->_material = MaterialManager::getInstance()->get(_name);
}

void Entity::recreate(int _index) {
}

void Entity::updateDescriptors(int _index, VkDescriptorSet _descriptorSet) {
	this->_uniformBuffer->updateDescriptor(_index, _descriptorSet, 0);
	this->_texture->getBuffer()->updateDescriptor(_index, _descriptorSet, 1);
	this->_colorBuffer->updateDescriptor(_index, _descriptorSet, 2);
}

Entity::~Entity() {
	delete _mesh;
	delete _uniformBuffer;
	delete _colorBuffer;
	delete _texture;
}
