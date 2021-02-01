#include "resourcemanager.h"

static ResourceManager* _instance;

ResourceManager::ResourceManager() {
	_textures = std::map<std::string, TextureBuffer*>();
	_meshes = std::map<MeshType, MeshBuffer*>();
	_objectMeshes = std::map<std::string, MeshBuffer*>();
}

ResourceManager* ResourceManager::getInstance() {
	if (!_instance) {
		_instance = new ResourceManager();
	}
	return _instance;
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

MeshBuffer* ResourceManager::getObjectMeshBuffer(const char* _path) {
	if (_objectMeshes[_path] != NULL) {
		return _objectMeshes[_path];
	}

	MeshBuffer* m = new MeshBuffer(MeshType::OBJECT, ModelLoader::loadObjectFile(_path));
	_objectMeshes[_path] = m;

	return _objectMeshes[_path];
}

void ResourceManager::deleteInstance() {
	delete _instance;
	_instance = nullptr;
}

ResourceManager::~ResourceManager() {
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

	// delete loaded object meshes
	std::map<std::string, MeshBuffer*>::iterator objmesh_it;
	for (objmesh_it = _objectMeshes.begin(); objmesh_it != _objectMeshes.end(); ++objmesh_it) {
		if (objmesh_it->second != NULL) {
			delete objmesh_it->second;
		}
	}
	_objectMeshes.clear();
}

