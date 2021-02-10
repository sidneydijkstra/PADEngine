#include "material.h"

MaterialBuffer::MaterialBuffer(MaterialData _data) {
	this->_name = _data.name;
	this->_shaderEffect = new ShaderEffect(_data.vertexPath, _data.fragmentPath);

	if(_data.customShader)
		this->_shaderPass = new ShaderPass(_data.renderPass->getRenderPass(), this->_shaderEffect, _data.descriptorLayout, _data.descriptorLayoutSize, _data.descriptorPool, _data.descriptorPoolSize);
	else
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
