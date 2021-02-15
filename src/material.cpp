
#include "material.h"

namespace pad {

Material::Material(const char* _name) {
	this->_bufferObject = new UniformBuffer<MaterialBufferObject>();
	this->_pool = nullptr;

	this->color = WHITE;
	this->ambient = Vector3(1.0f, 0.5f, 0.31f);
	this->diffuse = Vector3(1.0f, 0.5f, 0.31f);
	this->specular = Vector3(0.5f, 0.5f, 0.5f);
	this->shininess = 32.0f;

	this->setup(_name);
}

VkDescriptorPool& Material::getPool() {
	return this->_pool->getPool();
}

MaterialBuffer* Material::getMaterialBuffer() {
	return this->_buffer;
}

UniformBuffer<MaterialBufferObject>* Material::getMaterialUniformBuffer() {
	return this->_bufferObject;
}

void Material::setMaterial(const char* _name){
	this->setup(_name);
}

void Material::updateDescriptors(int _index, VkDescriptorSet _descriptorSet) {
	this->_bufferObject->updateBuffer(_index, MaterialBufferObject{ color, ambient, diffuse, specular, shininess });
	this->_bufferObject->updateDescriptor(_index, _descriptorSet, 2);
}

void Material::setup(const char* _name) {
	if (this->_pool != nullptr)
		this->_buffer->getDescriptor()->freePool(this->_pool);

	this->_buffer = MaterialManager::getInstance()->getMaterial(_name);

	this->_pool = _buffer->getDescriptor()->getPool();
}

Material::~Material() {
	if (this->_pool != nullptr)
		this->_buffer->getDescriptor()->freePool(this->_pool);

	delete this->_bufferObject;
}

}
