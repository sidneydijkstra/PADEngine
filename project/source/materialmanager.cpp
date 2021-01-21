#include "materialmanager.h"

static MaterialManager* _instance;

MaterialManager::MaterialManager() {
	_materials = std::map<std::string, Material*>();
}

MaterialManager* MaterialManager::getInstance() {
	if (!_instance) {
		_instance = new MaterialManager();
	}
	return _instance;
}

void MaterialManager::deleteInstance() {
	delete _instance;
	_instance = nullptr;
}

void MaterialManager::load(const char* _name, ShaderPass* _shaderPass) {
	Material* t = new Material(_name, _shaderPass);
	std::cout << _name << " => " << " -> material loaded" << '\n';

	_materials[_name] = t;
}

Material* MaterialManager::get(const char* _name) {
	if (_materials[_name] != NULL) {
		return _materials[_name];
	}
}

MaterialManager::~MaterialManager() {
	std::map<std::string, Material*>::iterator mat_it;
	for (mat_it = _materials.begin(); mat_it != _materials.end(); ++mat_it) {
		if (mat_it->second != NULL) {
			delete mat_it->second;
		}
	}
	_materials.clear();
}
