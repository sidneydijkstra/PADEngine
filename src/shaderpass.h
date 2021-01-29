
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

class PipelineFactory {
	public:
		static VkViewport getViewport() {
			VkViewport viewport{};
			viewport.x = 0.0f;
			viewport.y = 0.0f;
			viewport.width = (float)SwapChainHandler::getInstance()->getSwapChainWidth();
			viewport.height = (float)SwapChainHandler::getInstance()->getSwapChainHeight();
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			return viewport;
		};

		static VkRect2D getRect2D() {
			VkRect2D scissor{};
			scissor.offset = { 0, 0 };
			scissor.extent = SwapChainHandler::getInstance()->getSwapChainExtent();
			return scissor;
		};

		static VkPipelineViewportStateCreateInfo getViewportStateCreateInfo(VkViewport& _viewport, VkRect2D& _scissor) {
			VkPipelineViewportStateCreateInfo viewportState{};
			viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewportState.viewportCount = 1;
			viewportState.pViewports = &_viewport;
			viewportState.scissorCount = 1;
			viewportState.pScissors = &_scissor;
			return viewportState;
		};

		static VkPipelineRasterizationStateCreateInfo getRasterizationStateCreateInfo() {
			VkPipelineRasterizationStateCreateInfo rasterizer{};
			rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			rasterizer.depthClampEnable = VK_FALSE;
			rasterizer.rasterizerDiscardEnable = VK_FALSE;
			rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
			rasterizer.lineWidth = 1.0f;
			rasterizer.cullMode = VK_CULL_MODE_FRONT_BIT; //VK_CULL_MODE_NONE; TODO: watch
			rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
			rasterizer.depthBiasEnable = VK_FALSE;
			rasterizer.depthBiasConstantFactor = 0.0f; // Optional
			rasterizer.depthBiasClamp = 0.0f; // Optional
			rasterizer.depthBiasSlopeFactor = 0.0f; // Optional
			return rasterizer;
		};

		static VkPipelineMultisampleStateCreateInfo getMultisampleStateCreateInfo() {
			VkPipelineMultisampleStateCreateInfo multisampling{};
			multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			multisampling.sampleShadingEnable = VK_TRUE; // enable sample shading in the pipeline
			multisampling.minSampleShading = .2f; // min fraction for sample shading; closer to one is smoother
			multisampling.rasterizationSamples = DeviceHandler::getInstance()->getMsaaSamples();
			multisampling.pSampleMask = nullptr; // Optional
			multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
			multisampling.alphaToOneEnable = VK_FALSE; // Optional
			return multisampling;
		};

		static VkPipelineColorBlendAttachmentState getColorBlendAttachment() {
			VkPipelineColorBlendAttachmentState colorBlendAttachment{};
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_FALSE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional
			return colorBlendAttachment;
		};

		static VkPipelineColorBlendStateCreateInfo getColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState& _colorBlendAttachment) {
			VkPipelineColorBlendStateCreateInfo colorBlending{};
			colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			colorBlending.logicOpEnable = VK_FALSE;
			colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
			colorBlending.attachmentCount = 1;
			colorBlending.pAttachments = &_colorBlendAttachment;
			colorBlending.blendConstants[0] = 0.0f; // Optional
			colorBlending.blendConstants[1] = 0.0f; // Optional
			colorBlending.blendConstants[2] = 0.0f; // Optional
			colorBlending.blendConstants[3] = 0.0f; // Optional
			return colorBlending;
		};

		static VkPipelineDynamicStateCreateInfo getDynamicStateCreateInfo(VkDynamicState _dynamicStates[]) {
			VkPipelineDynamicStateCreateInfo dynamicState{};
			dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			dynamicState.dynamicStateCount = sizeof(_dynamicStates) / sizeof(VkDynamicState);
			dynamicState.pDynamicStates = _dynamicStates;
			return dynamicState;
		};

		static VkPipelineDepthStencilStateCreateInfo getDepthStencilStateCreateInfo() {
			VkPipelineDepthStencilStateCreateInfo depthStencil{};
			depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			depthStencil.depthTestEnable = VK_TRUE;
			depthStencil.depthWriteEnable = VK_TRUE;
			depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
			depthStencil.depthBoundsTestEnable = VK_FALSE;
			depthStencil.minDepthBounds = 0.0f; // Optional
			depthStencil.maxDepthBounds = 1.0f; // Optional
			depthStencil.stencilTestEnable = VK_FALSE;
			depthStencil.front = {}; // Optional
			depthStencil.back = {}; // Optional
			return depthStencil;
		};

		static VkPipelineLayoutCreateInfo getPiplineLayoutCreateInfo(const VkDescriptorSetLayout& _layout) {
			VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = 1;
			pipelineLayoutInfo.pSetLayouts = &_layout;
			pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
			pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional
			return pipelineLayoutInfo;
		};
};

#endif