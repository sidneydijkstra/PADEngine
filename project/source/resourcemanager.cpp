#include "resourcemanager.h"

static ResourceManager* _instance;

ResourceManager::ResourceManager() {
	_entityDescriptor = new Descriptor();
	_textures = std::map<std::string, TextureBuffer*>();
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

void ResourceManager::deleteInstance() {
	delete _instance;
	_instance = nullptr;
}

ResourceManager::~ResourceManager() {
	delete _entityDescriptor;

	std::map<std::string, TextureBuffer*>::iterator text_it;
	for (text_it = _textures.begin(); text_it != _textures.end(); ++text_it) {
		if (text_it->second != NULL) {
			std::cout << text_it->first << " => " << text_it->second << '\n';
			delete text_it->second;
		}
	}
	_textures.clear();
}

