/// @file shadermanager.h
/// @brief Standalone header providing ShaderManager functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef SHADERMANAGER_CLASS
#define SHADERMANAGER_CLASS

#include "shaderstage.h"

#include <iostream>
#include <map>

namespace pad {

/// @brief Class describing a ShaderManager, which stores all the ShaderStage pointers.
///
/// The ShaderManager manages the loading of different Shaders used in the game. 
/// The manager ensures that these objects are not loaden continuously but only once and are reused when requested multiple times. 
/// This saves a lot of memory space when working on bigger projects.

class ShaderManager {
	public:
		/// @brief The constructor for the ShaderManager class.
		ShaderManager();
		/// @brief The deconstructor for the ShaderManager class.
		~ShaderManager();

		/// @brief Static get instance function, ShaderManager is a singelton because we only need one instance.
		/// @return A pointer to ShaderManager.
		static ShaderManager* getInstance();
		/// @brief Static function to delete and cleanup the ShaderManager.
		static void deleteInsance();

		/// @brief Get a ShaderStage pointer.
		/// @param _path Path to shader file.
		/// @param _stage Shader stage flag bits.
		/// @return Pointer to ShaderStage.
		ShaderStage* getShaderStage(const char* _path, VkShaderStageFlagBits _stage);

	private:
		std::map<std::string, ShaderStage*> _shaderStages; ///< @brief A std::map with ShaderStage pointers arranged by path.
};

}

#endif