#include "shadereffect.h"

ShaderEffect::ShaderEffect(const char* _vertexPath, const char* _fragmentPath) {
	_stages = std::vector<ShaderStage*>();
	_stages.push_back(ShaderManager::getInstance()->getShaderStage(_vertexPath, VK_SHADER_STAGE_VERTEX_BIT));
	_stages.push_back(ShaderManager::getInstance()->getShaderStage(_fragmentPath, VK_SHADER_STAGE_FRAGMENT_BIT));
}

std::vector<ShaderStage*> ShaderEffect::getStages() {
	return this->_stages;
}

ShaderEffect::~ShaderEffect() {
	_stages.clear();
}

