#include "material.h"

namespace pad {

MaterialBuffer::MaterialBuffer(MaterialData _data) {
	this->_name = _data.name;
	this->_shaderPass = new ShaderPass(_data);
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
	delete this->_shaderPass;
}

}
