/// @file modelloader.h
/// @brief Standalone header providing ModelLoader functionality.
/// @author Naomi Poort
/// @version 1.0.0
/// @date 02/01/2021

#ifndef MODELLOADER_CLASS
#define MODELLOADER_CLASS

#include <unordered_map>

#include "vertex.h"
#include "meshbuffer.h"

/// @brief Class describing a ModelLoader object, this class is used to load .obj files.
class ModelLoader {
	public:
		/// @brief Function to load a .obj file to Vertex's and indicies.
		/// @param obj_file_path Path to object file.
		/// @return MeshData object containing Vertex's and indicies.
		static MeshData loadObjectFile(std::string obj_file_path);
};
#endif
