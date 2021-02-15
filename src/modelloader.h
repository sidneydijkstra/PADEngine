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

namespace pad {

/// @brief Class describing a ModelLoader object, this class is used to load .obj files.
///
/// The Modelloader is exclusively meant for loading .obj file, which are files that contain information about a specific model, for example their verticies and positions of those verticies, texture mapping and more.
/// This loaded model is then saved in the ResourceManager.

class ModelLoader {
	public:
		/// @brief Function to load a .obj file to Vertex's and indicies.
		/// @param obj_file_path Path to object file.
		/// @return MeshData object containing Vertex's and indicies.
		static MeshData loadObjectFile(std::string obj_file_path);
};

}

#endif
