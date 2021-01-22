
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <map>

#include "descriptor.h"
#include "texturebuffer.h"
#include "meshbuffer.h"
#include "modelloader.h"

class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();

		static ResourceManager* getInstance();
		static void deleteInstance();

		TextureBuffer* getTextureBuffer(const char* path);
		MeshBuffer* getMeshBuffer(MeshType _type);
		MeshBuffer* getObjectMeshBuffer(const char* _path);
	private:
		std::map<std::string, TextureBuffer*> _textures;
		std::map<MeshType, MeshBuffer*> _meshes;
		std::map<std::string, MeshBuffer*> _objectMeshes;
};
#endif