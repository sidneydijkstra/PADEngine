#include "material.h"

Material::Material(const char* _name, ShaderPass* _shaderPass) {
	this->_name = _name;
	this->_shaderPass = _shaderPass;
}

std::string Material::getName() {
	return this->_name;
}

Descriptor* Material::getDescriptor() {
	return this->_shaderPass->getDescriptor();
}

ShaderPass* Material::getShaderPass() {
	return this->_shaderPass;
}

Material::~Material() {
}
