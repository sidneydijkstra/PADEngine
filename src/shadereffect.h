/// @file shadereffect.h
/// @brief Standalone header providing ShaderEffect functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef SHADEREFFECT_CLASS
#define SHADEREFFECT_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"
#include "resourcemanager.h"
#include "shadermanager.h"
#include "descriptor.h"
#include "vertex.h"

#include "shaderstage.h"

#include <iostream>
#include <vector>
#include <string>

/// @brief Class describing a ShaderEffect object, which stores ShaderStage for a ShaderPass.
///
/// The ShaderEffect class consists of two ShaderStage objects. 
/// These objects represent the vertex shader and the fragment shader. 
/// These are not created inside the ShaderEffect class but fetched from the ShaderManager. 
/// This way another ShaderEffect instance can make use of these earlier determined vertex or fragment shader, without having to load the file repeatedly. 
/// This will save a lot of memory space in bigger projects.

class ShaderEffect {
	public:
		/// @brief The constructor for the ShaderEffect class.
		/// @param _vertexPath Path to vertex shader file.
		/// @param _fragmentPath Path to fragment shader file.
		ShaderEffect(const char* _vertexPath, const char* _fragmentPath);
		/// @brief The constructor for the ShaderEffect class.
		~ShaderEffect();

		/// @brief Get all the ShaderStage.
		/// @return A std::vector of ShaderStage.
		std::vector<ShaderStage*> getStages();

	protected:
		std::vector<ShaderStage*> _stages; ///< @brief A std::vector containing ShaderStage pointers.
};

#endif