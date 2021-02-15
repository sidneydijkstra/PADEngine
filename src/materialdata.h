/// @file materialdata.h
/// @brief Standalone header providing MaterialData strukt.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021


#ifndef MATERIALDATA_CLASS
#define MATERIALDATA_CLASS

#include "renderpass.h"

/// @brief Class holding config information.
///
/// MaterialData is a struct containing information to create a MaterialBuffer. 
/// You have standard information about the Material like the name of the shader and the paths to the vertex/fragment shader. 
/// You also have the option to create a custom shader using the flag customShader, then you can set the <a href=”https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorSetLayoutBinding.html”> VkDescriptorSetLayoutBinding </a> and <a href=”https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorPoolSize.html”> VkDescriptorPoolSize </a> to tell the shader the type of data you want to send to it.
struct MaterialData {
	const char* name;
	RenderPass* renderPass;
	const char* vertexPath;
	const char* fragmentPath;
	bool customShader = false;
	VkDescriptorSetLayoutBinding* descriptorLayout;
	int descriptorLayoutSize;
	VkDescriptorPoolSize* descriptorPool;
	int descriptorPoolSize;
};

#endif