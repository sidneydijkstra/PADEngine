#include "material.h"

Material::Material(MaterialData _data) {
	this->_name = _data.name;
	this->_shaderEffect = new ShaderEffect(_data.vertexPath, _data.fragmentPath);
	this->_shaderPass = new ShaderPass(_data.renderPass->getRenderPass(), this->_shaderEffect);
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
	delete this->_shaderEffect;
	delete this->_shaderPass;
}
