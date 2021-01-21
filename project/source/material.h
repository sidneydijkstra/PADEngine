
#ifndef MATERIAL_CLASS
#define MATERIAL_CLASS

#include "shaderpass.h";
#include "shadereffect.h"

struct MaterialData {
	ShaderEffect* shaderEffect;
	ShaderPass* shaderPass;
	VkRenderPass renderPass;
};

class Material {
	public:
		Material(const char* _name, ShaderPass* _shaderPass);
		~Material();

		std::string getName();
		Descriptor* getDescriptor();
		ShaderPass* getShaderPass();

	private:
		std::string _name;
		ShaderPass* _shaderPass;
};
#endif