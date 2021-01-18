#include "resourcemanager.h"

static ResourceManager* _instance;

ResourceManager::ResourceManager() {
	_entityDescriptor = new Descriptor();
	_textures = std::map<std::string, TextureBuffer*>();
	_meshes = std::map<MeshType, MeshBuffer*>();
}

ResourceManager* ResourceManager::getInstance() {
	if (!_instance) {
		_instance = new ResourceManager();
	}
	return _instance;
}

Descriptor* ResourceManager::getEntityDescriptor() {
	return _entityDescriptor;
}

TextureBuffer* ResourceManager::getTextureBuffer(const char* path) {
	if (_textures[path] != NULL) {
		return _textures[path];
	}

	TextureBuffer* t = new TextureBuffer(path);
	std::cout << path << " => " << " -> loaded" << '\n';

	_textures[path] = t;

	return _textures[path];
}

MeshBuffer* ResourceManager::getMeshBuffer(MeshType _type) {
	if (_meshes[_type] != NULL) {
		return _meshes[_type];
	}

	MeshBuffer* t = new MeshBuffer(_type);
	_meshes[_type] = t;

	return _meshes[_type];
}

void ResourceManager::deleteInstance() {
	delete _instance;
	_instance = nullptr;
}

ResourceManager::~ResourceManager() {
	delete _entityDescriptor;

	// delete loaded textures
	std::map<std::string, TextureBuffer*>::iterator text_it;
	for (text_it = _textures.begin(); text_it != _textures.end(); ++text_it) {
		if (text_it->second != NULL) {
			delete text_it->second;
		}
	}
	_textures.clear();

	// delete loaded meshes
	std::map<MeshType, MeshBuffer*>::iterator mesh_it;
	for (mesh_it = _meshes.begin(); mesh_it != _meshes.end(); ++mesh_it) {
		if (mesh_it->second != NULL) {
			delete mesh_it->second;
		}
	}
	_meshes.clear();
}

