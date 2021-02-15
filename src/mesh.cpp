#include "mesh.h"

namespace pad {

Mesh::Mesh() {
	_meshBuffer = ResourceManager::getInstance()->getMeshBuffer(MeshType::PLANE);
}

void Mesh::loadShape(MeshType _type) {
	_meshBuffer = ResourceManager::getInstance()->getMeshBuffer(_type);
}

void Mesh::loadObject(const char* _path) {
	_meshBuffer = ResourceManager::getInstance()->getObjectMeshBuffer(_path);
}

MeshBuffer* Mesh::getBuffer() {
	return _meshBuffer;
}

MeshType Mesh::getType() {
	return this->_meshBuffer->getType();
}

Mesh::~Mesh() {
}

}
