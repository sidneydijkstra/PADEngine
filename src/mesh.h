/// @file mesh.h
/// @brief Standalone header providing Mesh functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef MESH_CLASS
#define MESH_CLASS

#include "resourcemanager.h"
#include "meshbuffer.h"

/// @brief Class describing a Mesh object, which stores all the information for a 2D/3D Mesh.
class Mesh {
	public:
		/// @brief The constructor for the Mesh class.
		Mesh();
		/// @brief The deconstructor for the Mesh class.
		~Mesh();

		/// @brief Load a shape.
		/// @param _type MeshType to load.
		void loadShape(MeshType _type);

		/// @brief Load a object.
		/// @param _path Path to object file.
		void loadObject(const char* _path);

		/// @brief Get the MeshBuffer pointer.
		/// @return Pointer to MeshBuffer.
		MeshBuffer* getBuffer();

		/// @brief Get the MeshType.
		/// @return Current MeshType.
		MeshType getType();

	private:
		MeshBuffer* _meshBuffer; ///< @brief MeshBuffer object pointer of Mesh.
};
#endif