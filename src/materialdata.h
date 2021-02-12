/// @file materialdata.h
/// @brief Standalone header providing MaterialData strukt.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021


#ifndef MATERIALDATA_CLASS
#define MATERIALDATA_CLASS

#include "renderpass.h"

/// @brief Class holding config information.
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