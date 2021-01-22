#ifndef MODELLOADER_CLASS
#define MODELLOADER_CLASS

#include <unordered_map>

#include "vertex.h"
#include "meshbuffer.h"

class ModelLoader {
	public:
		static MeshData ModelLoader::loadObjectFile(std::string obj_file_path);
};
#endif
