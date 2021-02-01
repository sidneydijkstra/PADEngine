
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

		void load(MaterialData _data);
		Material* get(const char* _name);

		void recreateAll();

	private:
		std::map<std::string, Material*> _materials;
};
#endif