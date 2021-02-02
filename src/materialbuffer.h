/// @file material.h
/// @brief Standalone header providing Material functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef MATERIALBUFFER_CLASS
#define MATERIALBUFFER_CLASS

#include "renderpass.h"
#include "shaderpass.h"
#include "shadereffect.h"

struct MaterialData {
	const char* name;
	RenderPass* renderPass;
	const char* vertexPath;
	const char* fragmentPath;
};

class MaterialBuffer {
	public:
		MaterialBuffer(MaterialData _data);
		~MaterialBuffer();

		std::string getName();
		Descriptor* getDescriptor();
		ShaderPass* getShaderPass();

	private:
		std::string _name;
		ShaderEffect* _shaderEffect;
		ShaderPass* _shaderPass;
};
#endif