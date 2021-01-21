
#ifndef MATERIALMANAGER_CLASS
#define MATERIALMANAGER_CLASS

#include "material.h"

#include <iostream>
#include <map>

class MaterialManager {
	public:
		MaterialManager();
		~MaterialManager();

		static MaterialManager* getInstance();
		static void deleteInstance();

		void load(const char* _name, ShaderPass* _shaderPass);
		Material* get(const char* _name);

	private:
		std::map<std::string, Material*> _materials;
};
#endif