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

/// @brief The MaterialManager class is the resourcemanager for the MaterialBuffer objects. 
///
/// this class creates these objects and hold there pointers. This way when we create an Entity its Material class gets a MaterialBuffer pointer from this class.
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
#endif