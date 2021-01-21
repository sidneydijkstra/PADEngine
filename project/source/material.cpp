#include "material.h"

Material::Material(ShaderPass* _shaderPass) {
	this->_shaderPass = _shaderPass;
}

Descriptor* Material::getDescriptor() {
	return this->_shaderPass->getDescriptor();
}

ShaderPass* Material::getShaderPass() {
	return this->_shaderPass;
}

Material::~Material() {
}
