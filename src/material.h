
#ifndef MATERIAL_CLASS
#define MATERIAL_CLASS

#include "renderpass.h"
#include "shaderpass.h"
#include "shadereffect.h"

struct MaterialData {
	const char* name;
	RenderPass* renderPass;
	const char* vertexPath;
	const char* fragmentPath;
};

class Material {
	public:
		Material(MaterialData _data);
		~Material();

		std::string getName();
		Descriptor* getDescriptor();
		ShaderPass* getShaderPass();

	private:
		std::string _name;
		ShaderEffect* _shaderEffect;
		ShaderPass* _shaderPass;
};
#endif