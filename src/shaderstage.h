/// @file shaderstage.h
/// @brief Standalone header providing ShaderStage functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef SHADERSTAGE_CLASS
#define SHADERSTAGE_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"
#include "vertex.h"

#include <iostream>
#include <vector>
#include <string>

/// @brief Class describing a ShaderStage object, which stores all the information for a shader stage.
///
/// The ShaderStage class contains a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkShaderModule.html">VkShaderModule</a> that’s created with the shader code created from a shader file.
/// This will then in turn be used for creating a <a href=" https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkPipelineShaderStageCreateInfo.html ">VkPipelineShaderStageCreateInfo</a> object. 
/// Which is needed to create a Shader.

class ShaderStage {
	public:
		/// @brief The constructor for the Entity class.
		/// @param _path Path to shader file.
		/// @param _stage Shader stage flag bits.
		ShaderStage(const char* _path, VkShaderStageFlagBits _stage);
		/// @brief The constructor for the Entity class.
		~ShaderStage();

		/// @brief Get the shader stage create info.
		/// @return The VkPipelineShaderStageCreateInfo.
		VkPipelineShaderStageCreateInfo getStateInfo();

	private:
		std::vector<char> _shaderCode; ///< @brief A std::vector with shader code.
		VkShaderModule _shaderModule; ///< @brief VkShaderModule of ShaderStage.
		VkPipelineShaderStageCreateInfo _stageInfo; ///< @brief VkPipelineShaderStageCreateInfo of ShaderStage.

		/// @brief Read a shader file.
		/// @param _filename Name of shader file.
		/// @return A std::vector with shader code.
		std::vector<char> readFile(const std::string& _filename);

		/// @brief Create a VkShaderModule from shader code.
		/// @param _code Shader code.
		/// @return The VkShaderModule.
		VkShaderModule createShaderModule(const std::vector<char>& _code);
};

#endif