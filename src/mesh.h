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
///
/// In 3D computer graphics and solid modeling, a polygon mesh is a collection of vertices, edges and faces that defines the shape of a polyhedral object. 
/// The faces usually consist of triangles, quadrilaterals, or other simple convex polygons, since this simplifies rendering, but may also be more generally composed of concave polygons, or even polygons with holes.
/// In short the Mesh creates a model that can be renderd on screen through a list of vertecies and their coordinates.

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