#include "material.h"

MaterialBuffer::MaterialBuffer(MaterialData _data) {
	this->_name = _data.name;
	this->_shaderEffect = new ShaderEffect(_data.vertexPath, _data.fragmentPath);
	this->_shaderPass = new ShaderPass(_data.renderPass->getRenderPass(), this->_shaderEffect);
}

std::string MaterialBuffer::getName() {
	return this->_name;
}

Descriptor* MaterialBuffer::getDescriptor() {
	return this->_shaderPass->getDescriptor();
}

ShaderPass* MaterialBuffer::getShaderPass() {
	return this->_shaderPass;
}

MaterialBuffer::~MaterialBuffer() {
	delete this->_shaderEffect;
	delete this->_shaderPass;
}
