
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <map>

#include "descriptor.h"
#include "texturebuffer.h"

class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();

		static ResourceManager* getInstance();
		static void deleteInstance();

		Descriptor* getEntityDescriptor();
		TextureBuffer* getTextureBuffer(const char* path);
	private:
		Descriptor* _entityDescriptor;
		std::map<std::string, TextureBuffer*> _textures;
};
#endif