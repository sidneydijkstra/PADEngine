#include "meshbuffer.h"

MeshBuffer::MeshBuffer() {
	_indexBuffer = new IndexBuffer(cube_indices);
	_vertexBuffer = new VertexBuffer(cube_vertices);
	_type = MeshType::CUBE;
}

MeshBuffer::MeshBuffer(MeshType _type, MeshData _data) {
	_indexBuffer = new IndexBuffer(_data.indices);
	_vertexBuffer = new VertexBuffer(_data.vertices);
	this->_type = _type;
}

MeshType MeshBuffer::getType() {
	return this->_type;
}

IndexBuffer* MeshBuffer::index() {
	return _indexBuffer;
}

VertexBuffer* MeshBuffer::vertex() {
	return _vertexBuffer;
}

MeshBuffer::MeshBuffer(MeshType _type) {
	this->_type = _type;
	switch (_type) {
		case MeshType::TRIANGLE:
			_indexBuffer = new IndexBuffer(plane_indices);
			_vertexBuffer = new VertexBuffer(plane_vertices);
			break;
		case MeshType::PLANE:
			_indexBuffer = new IndexBuffer(plane_indices);
			_vertexBuffer = new VertexBuffer(plane_vertices);
			break;
		case MeshType::CUBE:
			_indexBuffer = new IndexBuffer(cube_indices);
			_vertexBuffer = new VertexBuffer(cube_vertices);
			break;
		default:
			_indexBuffer = new IndexBuffer(plane_indices);
			_vertexBuffer = new VertexBuffer(plane_vertices);
			break;
	}
}

MeshBuffer::~MeshBuffer() {
	delete _indexBuffer;
	delete _vertexBuffer;
}
