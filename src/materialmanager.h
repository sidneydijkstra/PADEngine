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

namespace pad {

/// @brief Class describing a MaterialManager, which stores all the pointers to frequently used Materials.
///
/// The ResourceManager manages the loading of different Materials used in the game. 
/// The manager ensures that these objects are not loaden continuously but only once and are reused when requested multiple times. 
/// This saves a lot of memory space when working on bigger projects.
class MaterialManager {
	public:
		/// @brief The constructor for the MaterialManager class.
		MaterialManager();
		/// @brief The deconstructor for the MaterialManager class.
		~MaterialManager();

		/// @brief Static get instance function, MaterialManager is a singelton because we only need one instance.
		/// @return A pointer to MaterialManager.
		static MaterialManager* getInstance();
		/// @brief Static function to delete and cleanup the ResourceManager.
		static void deleteInstance();

		/// @brief Function to load a new MaterialBuffer from a MaterialData struct.
		/// @param _data MaterialData struct to load MaterialBuffer from.
		void loadMaterial(MaterialData _data);

		/// @brief Function to get a MaterialBuffer from a Material name.
		/// @param _name Name of Material to get.
		/// @return MaterialBuffer poitner.
		MaterialBuffer* getMaterial(const char* _name);

		/// @brief Function to recreate all MaterialBuffer objects.
		void recreateAll();

	private:
		std::map<std::string, MaterialBuffer*> _materials;
};

}

#endif