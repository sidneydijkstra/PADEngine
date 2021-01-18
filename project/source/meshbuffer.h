
#ifndef MESHBUFFER_CLASS
#define MESHBUFFER_CLASS

#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "uniformbuffer.h"

enum MeshType {
	TRYANGLE, PLANE, CUBE
};

class MeshBuffer {
	public:
		MeshBuffer();
		MeshBuffer(MeshType _type);
		~MeshBuffer();

		MeshType getType();
		IndexBuffer* index();
		VertexBuffer* vertex();

	private:
		MeshType _type;
		IndexBuffer* _indexBuffer;
		VertexBuffer* _vertexBuffer;

		const std::vector<uint16_t> plane_indices = {
			0, 1, 2, 2, 3, 0
		};

		const std::vector<Vertex> plane_vertices = {
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};

		const std::vector<uint16_t> cube_indices = {
			 0,  1,  2,  2,  3,  0,
			 4,  5,  6,  6,  7,  4,
			 8,  9, 10, 10, 11,  8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20,
		};

		const std::vector<Vertex> cube_vertices = {
			{{-0.5f, -0.5f, -0.5f},  {1.0f,  1.0f, 1.0f},  {0.0f, 0.0f}},
			{{ 0.5f, -0.5f, -0.5f},  {1.0f,  1.0f, 1.0f},  {1.0f, 0.0f}},
			{{ 0.5f,  0.5f, -0.5f},  {1.0f,  1.0f, 1.0f},  {1.0f, 1.0f}},
			{{-0.5f,  0.5f, -0.5f},  {1.0f,  1.0f, 1.0f},  {0.0f, 1.0f}},

			{{-0.5f, -0.5f,  0.5f},  {1.0f,  1.0f, 1.0f},   {0.0f, 0.0f}},
			{{ 0.5f, -0.5f,  0.5f},  {1.0f,  1.0f, 1.0f},   {1.0f, 0.0f}},
			{{ 0.5f,  0.5f,  0.5f},  {1.0f,  1.0f, 1.0f},   {1.0f, 1.0f}},
			{{-0.5f,  0.5f,  0.5f},  {1.0f,  1.0f, 1.0f},   {0.0f, 1.0f}},

			{{-0.5f,  0.5f,  0.5f}, {1.0f,  1.0f,  1.0f},  {1.0f, 0.0f}},
			{{-0.5f,  0.5f, -0.5f}, {1.0f,  1.0f,  1.0f},  {1.0f, 1.0f}},
			{{-0.5f, -0.5f, -0.5f}, {1.0f,  1.0f,  1.0f},  {0.0f, 1.0f}},
			{{-0.5f, -0.5f,  0.5f}, {1.0f,  1.0f,  1.0f},  {0.0f, 0.0f}},

			{{ 0.5f,  0.5f,  0.5f},  {1.0f,  1.0f,  1.0f},  {1.0f, 0.0f}},
			{{ 0.5f,  0.5f, -0.5f},  {1.0f,  1.0f,  1.0f},  {1.0f, 1.0f}},
			{{ 0.5f, -0.5f, -0.5f},  {1.0f,  1.0f,  1.0f},  {0.0f, 1.0f}},
			{{ 0.5f, -0.5f,  0.5f},  {1.0f,  1.0f,  1.0f},  {0.0f, 0.0f}},

			{{-0.5f, -0.5f, -0.5f},  {1.0f, 1.0f,  1.0f},  {0.0f, 1.0f}},
			{{ 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f,  1.0f},  {1.0f, 1.0f}},
			{{ 0.5f, -0.5f,  0.5f},  {1.0f, 1.0f,  1.0f},  {1.0f, 0.0f}},
			{{-0.5f, -0.5f,  0.5f},  {1.0f, 1.0f,  1.0f},  {0.0f, 0.0f}},

			{{-0.5f,  0.5f, -0.5f},  {1.0f,  1.0f,  1.0f},  {0.0f, 1.0f}},
			{{ 0.5f,  0.5f, -0.5f},  {1.0f,  1.0f,  1.0f},  {1.0f, 1.0f}},
			{{ 0.5f,  0.5f,  0.5f},  {1.0f,  1.0f,  1.0f},  {1.0f, 0.0f}},
			{{-0.5f,  0.5f,  0.5f},  {1.0f,  1.0f,  1.0f},  {0.0f, 0.0f}},
		};
};
#endif