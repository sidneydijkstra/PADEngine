
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <map>

#include "descriptor.h"
#include "texturebuffer.h"
#include "meshbuffer.h"

class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();

		static ResourceManager* getInstance();
		static void deleteInstance();

		Descriptor* getEntityDescriptor();
		TextureBuffer* getTextureBuffer(const char* path);
		MeshBuffer* getMeshBuffer(MeshType _type);
	private:
		Descriptor* _entityDescriptor;
		std::map<std::string, TextureBuffer*> _textures;
		std::map<MeshType, MeshBuffer*> _meshes;
};
#endif