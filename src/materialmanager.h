/// @file materialmanager.h
/// @brief Standalone header providing MaterialManager functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef MATERIALMANAGER_CLASS
#define MATERIALMANAGER_CLASS

#include "materialbuffer.h"

#include <iostream>
#include <map>

class MaterialManager {
	public:
		MaterialManager();
		~MaterialManager();

		static MaterialManager* getInstance();
		static void deleteInstance();

		void load(MaterialData _data);
		MaterialBuffer* get(const char* _name);

		void recreateAll();

	private:
		std::map<std::string, MaterialBuffer*> _materials;
};
#endif