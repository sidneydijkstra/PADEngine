/// @file resourcemanager.h
/// @brief Standalone header providing ResourceManager functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

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

/// @brief Class describing a ResourceManager, which stores all the pointers to frequently used objects.
///
/// The ResourceManager manages the loading of different objects like textures, meshes and other resources used in the game. 
/// The manager ensures that these objects are not loaden continuously but only once and are reused when requested multiple times. 
/// This saves a lot of memory space when working on bigger projects.
class ResourceManager {
	public:
		/// @brief The constructor for the ResourceManager class.
		ResourceManager();
		/// @brief The deconstructor for the ResourceManager class.
		~ResourceManager();

		/// @brief Static get instance function, ResourceManager is a singelton because we only need one instance.
		/// @return A pointer to ResourceManager.
		static ResourceManager* getInstance();
		/// @brief Static function to delete and cleanup the ResourceManager.
		static void deleteInstance();

		/// @brief Get TextureBuffer by path.
		/// @param _path Path to texture file.
		/// @return Pointer to TextureBuffer.
		TextureBuffer* getTextureBuffer(const char* _path);

		/// @brief Get MeshBuffer by type.
		/// @param _type MeshType of MeshBuffer.
		/// @return Pointer to MeshBuffer.
		MeshBuffer* getMeshBuffer(MeshType _type);

		/// @brief Get MeshBuffer by object by path.
		/// @param _path Path to object file.
		/// @return Pointer to MeshBuffer.
		MeshBuffer* getObjectMeshBuffer(const char* _path);
	private:
		std::map<std::string, TextureBuffer*> _textures; ///< @brief A std::map containing TextureBuffer pointers arranged by path
		std::map<MeshType, MeshBuffer*> _meshes; ///< @brief A std::map containing MeshBuffer pointers arranged by MeshType
		std::map<std::string, MeshBuffer*> _objectMeshes; ///< @brief A std::map containing MeshBuffer pointers arranged by path
};
#endif