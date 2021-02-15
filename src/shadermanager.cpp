#include "shadermanager.h"

namespace pad {

static ShaderManager* _instance;

ShaderManager::ShaderManager() {
	_shaderStages = std::map<std::string, ShaderStage*>();
}

ShaderManager* ShaderManager::getInstance() {
	if (!_instance) {
		_instance = new ShaderManager();
	}
	return _instance;
}

ShaderStage* ShaderManager::getShaderStage(const char* _path, VkShaderStageFlagBits _stage) {
	if (_shaderStages[_path] != NULL) {
		return _shaderStages[_path];
	}

	ShaderStage* s = new ShaderStage(_path, _stage);
	_shaderStages[_path] = s;

	return _shaderStages[_path];
}

void ShaderManager::deleteInsance() {
	delete _instance;
	_instance = nullptr;
}

ShaderManager::~ShaderManager() {
	std::map<std::string, ShaderStage*>::iterator stage_it;
	for (stage_it = _shaderStages.begin(); stage_it != _shaderStages.end(); ++stage_it) {
		if (stage_it->second != NULL) {
			delete stage_it->second;
		}
	}
	_shaderStages.clear();
}

}
