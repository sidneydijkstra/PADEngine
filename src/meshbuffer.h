/// @file meshbuffer.h
/// @brief Standalone header providing Buffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef MESHBUFFER_CLASS
#define MESHBUFFER_CLASS

#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "uniformbuffer.h"

namespace pad {

/// @brief Enum describing a MeshType, which stores all the diffrent mesh types.
enum MeshType {
	TRIANGLE, PLANE, CUBE, OBJECT
};

/// @brief Struct describing a MeshData object, which stores all the vertices and indices.
struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};

/// @brief Class describing a MeshBuffer object, which stores all the buffers for a Mesh.
/// 
/// The MeshBuffer contains the necessary buffers for its task. 
/// For example, the MeshBuffer exists of a VertexBuffer and a IndexBuffer to create a mesh ready for rendering. 
/// Creating the mesh is executed in the ResourceManager so the same Mesh will only be loaded once and reused for every Entity containing the same Mesh data.
/// This is done to save a lot of memory space in bigger projects.

class MeshBuffer {
	public:
		/// @brief The constructor for the MeshBuffer class.
		MeshBuffer();
		/// @brief The constructor for the MeshBuffer class.
		/// @param _type The MeshType of this buffer.
		MeshBuffer(MeshType _type);
		/// @brief The constructor for the MeshBuffer class.
		/// @param _type The MeshType of this buffer.
		/// @param _data The MeshData of this buffer.
		MeshBuffer(MeshType _type, MeshData _data);
		/// @brief The deconstructor for the MeshBuffer class.
		~MeshBuffer();

		/// @brief Get the MeshType.
		/// @return Current MeshType.
		MeshType getType();

		/// @brief Get the IndexBuffer pointer.
		/// @return Pointer to IndexBuffer.
		IndexBuffer* index();

		/// @brief Get the VertexBuffer pointer.
		/// @return Pointer to VertexBuffer.
		VertexBuffer* vertex();

	private:
		MeshType _type; ///< @brief Variable storaing MeshType.
		IndexBuffer* _indexBuffer; ///< @brief IndexBuffer object pointer of MeshBuffer.
		VertexBuffer* _vertexBuffer; ///< @brief VertexBuffer object pointer of MeshBuffer.

		const std::vector<uint32_t> plane_indices = {
			0, 1, 2, 2, 3, 0
		};

		const std::vector<Vertex> plane_vertices = {
			{{-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
			{{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
			{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
			{{-1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};

		const std::vector<uint32_t> cube_indices = {
			 2,  1,  0,  0,  3,  2,
			 4,  5,  6,  6,  7,  4,
			 8,  9, 10, 10, 11,  8,
			14, 13, 12, 12, 15, 14,
			16, 17, 18, 18, 19, 16,
			22, 21, 20, 20, 23, 22
		};

		const std::vector<Vertex> cube_vertices = {
			{{-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},
			{{ 0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 0.0f}},
			{{ 0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
			{{-0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f, 1.0f}},

			{{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},   {0.0f, 0.0f}},
			{{ 0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},   {1.0f, 0.0f}},
			{{ 0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},   {1.0f, 1.0f}},
			{{-0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},   {0.0f, 1.0f}},

			{{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
			{{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
			{{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
			{{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},

			{{ 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
			{{ 0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
			{{ 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
			{{ 0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},

			{{-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f}},
			{{ 0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 1.0f}},
			{{ 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f}},
			{{-0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f, 0.0f}},

			{{-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
			{{ 0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f}},
			{{ 0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
			{{-0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f}}
		};
};

}

#endif