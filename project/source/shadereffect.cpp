#include "shadereffect.h"

ShaderEffect::ShaderEffect(const char* _vertexPath, const char* _fragmentPath) {
	_stages = std::vector<ShaderStage*>();
	_stages.push_back(new ShaderStage(_vertexPath, VK_SHADER_STAGE_VERTEX_BIT));
	_stages.push_back(new ShaderStage(_fragmentPath, VK_SHADER_STAGE_FRAGMENT_BIT));
}

std::vector<ShaderStage*> ShaderEffect::getStages() {
	return this->_stages;
}

ShaderEffect::~ShaderEffect() {
	for (size_t i = 0; i < _stages.size(); i++) {
		delete _stages[i];
	}
}

