/// @file material.h
/// @brief Standalone header providing Material functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef MATERIALBUFFER_CLASS
#define MATERIALBUFFER_CLASS

#include "materialdata.h"
#include "shaderpass.h"

namespace pad {

/// @brief Class describing a MaterialBuffer object, which stores all the buffers for a Material.
///
/// The MaterialBuffer contains the necessary buffers for its task. For example, the MaterialBuffer exists of a Shaderpass to create a Shader ready for rendering. 
/// Creating the Shader is executed in the ResourceManager so the same Shader will only be loaded once and reused for every Entity containing the same Shader data. This is done to save a lot of memory space in bigger projects.

class MaterialBuffer {
	public:
		/// @brief The constructor for the MaterialBuffer class.
		/// @param _data MaterialData struct to create material from
		MaterialBuffer(MaterialData _data);
		/// @brief The constructor for the MaterialBuffer class.
		~MaterialBuffer();

		/// @brief Get name of Material.
		/// @return Material name.
		std::string getName();

		/// @brief Get Descriptor pointer of Material.
		/// @return Descriptor pointer.
		Descriptor* getDescriptor();

		/// @brief Get ShaderPass pointer of Material.
		/// @return ShaderPass pointer.
		ShaderPass* getShaderPass();

	private:
		std::string _name;
		ShaderPass* _shaderPass;
};

}

#endif