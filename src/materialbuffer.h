/// @file material.h
/// @brief Standalone header providing Material functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef MATERIALBUFFER_CLASS
#define MATERIALBUFFER_CLASS

#include "materialdata.h"
#include "shaderpass.h"

/// @brief Class describing a MaterialBuffer object, which stores all the buffers for a Material.
///
/// The MaterialBuffer contains the necessary buffers for its task. For example, the MaterialBuffer exists of a Shaderpass to create a Shader ready for rendering. 
/// Creating the Shader is executed in the ResourceManager so the same Shader will only be loaded once and reused for every Entity containing the same Shader data. This is done to save a lot of memory space in bigger projects.

class MaterialBuffer {
	public:
		MaterialBuffer(MaterialData _data);
		~MaterialBuffer();

		std::string getName();
		Descriptor* getDescriptor();
		ShaderPass* getShaderPass();

	private:
		std::string _name;
		ShaderPass* _shaderPass;
};
#endif