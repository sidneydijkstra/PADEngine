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

/// @brief Class describing a MaterialManager, which stores all the pointers to frequently used Materials.
///
/// The ResourceManager manages the loading of different Materials used in the game. 
/// The manager ensures that these objects are not loaden continuously but only once and are reused when requested multiple times. 
/// This saves a lot of memory space when working on bigger projects.

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