#include "mesh.h"

Mesh::Mesh() {
	_meshBuffer = ResourceManager::getInstance()->getMeshBuffer(MeshType::PLANE);
}

void Mesh::loadShape(MeshType _type) {
	_meshBuffer = ResourceManager::getInstance()->getMeshBuffer(_type);
}

MeshBuffer* Mesh::getBuffer() {
	return _meshBuffer;
}

MeshType Mesh::getType() {
	return this->_meshBuffer->getType();
}

Mesh::~Mesh() {
}
