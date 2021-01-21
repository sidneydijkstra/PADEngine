
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
		Material(ShaderPass* _shaderPass);
		~Material();

		Descriptor* getDescriptor();
		ShaderPass* getShaderPass();

	private:
		ShaderPass* _shaderPass;
};
#endif