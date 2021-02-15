/// @file material.h
/// @brief Standalone header providing Material functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef MATERIALBUFFER_CLASS
#define MATERIALBUFFER_CLASS

#include "materialdata.h"
#include "shaderpass.h"

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