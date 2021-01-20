
#ifndef SHADERPASS_CLASS
#define SHADERPASS_CLASS

#include "descriptor.h"
#include "shadereffect.h"

class ShaderPass {
	public:
		ShaderPass(VkRenderPass _renderPass, ShaderEffect* _shaderEffect);
		~ShaderPass();

		Descriptor* getDescriptor();
		ShaderEffect* getShaderEffect();
		VkRenderPass getRenderPass();
		VkPipeline getPipeline();
		VkPipelineLayout getPipelineLayout();
		
		void recreate();

	private:
		ShaderEffect* _shaderEffect;
		VkRenderPass _renderPass;
		VkPipeline _pipeline;
		VkPipelineLayout _pipelineLayout;
		Descriptor* _descriptor;

		void setup();
};

#endif