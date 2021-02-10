#include "shaderpass.h"

ShaderPass::ShaderPass(VkRenderPass _renderPass, ShaderEffect* _shaderEffect) {
	this->_descriptor = new Descriptor();

	this->_shaderEffect = _shaderEffect;
	this->_renderPass = _renderPass;

	this->setup();
}

ShaderPass::ShaderPass(VkRenderPass _renderPass, ShaderEffect* _shaderEffect, VkDescriptorSetLayoutBinding* _descriptorLayout, int _descriptorLayoutSize, VkDescriptorPoolSize* _descriptorPool, int _descriptorPoolSize) {
	this->_descriptor = new Descriptor(_descriptorLayout, _descriptorLayoutSize, _descriptorPool, _descriptorPoolSize);

	this->_shaderEffect = _shaderEffect;
	this->_renderPass = _renderPass;

	this->setup();
}

Descriptor* ShaderPass::getDescriptor() {
	return this->_descriptor;
}

ShaderEffect* ShaderPass::getShaderEffect() {
	return this->_shaderEffect;
}

VkRenderPass ShaderPass::getRenderPass() {
	return this->_renderPass;
}

VkPipeline ShaderPass::getPipeline() {
	return this->_pipeline;
}

VkPipelineLayout ShaderPass::getPipelineLayout() {
	return this->_pipelineLayout;
}

void ShaderPass::recreate() {
	vkDestroyPipeline(DeviceHandler::getInstance()->getLogicalDevice(), this->_pipeline, nullptr);
	vkDestroyPipelineLayout(DeviceHandler::getInstance()->getLogicalDevice(), this->_pipelineLayout, nullptr);

	this->setup();
}

void ShaderPass::setup() {
	/* create pipline layout [START] */
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = PipelineFactory::getPiplineLayoutCreateInfo(_descriptor->getLayout());

	if (vkCreatePipelineLayout(DeviceHandler::getInstance()->getLogicalDevice(), &pipelineLayoutInfo, nullptr, &this->_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}
	else {
		std::cout << "created pipeline layout!" << std::endl;
	}
	/* create pipline layout [END] */

	std::vector<ShaderStage*> stages = _shaderEffect->getStages();

	VkPipelineShaderStageCreateInfo shaderStages[] = { stages[0]->getStateInfo(), stages[1]->getStateInfo() };

	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	auto bindingDescription = Vertex::getBindingDescription();
	auto attributeDescriptions = Vertex::getAttributeDescriptions();

	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = PipelineFactory::getViewport();
	VkRect2D scissor = PipelineFactory::getRect2D();
	VkPipelineViewportStateCreateInfo viewportState = PipelineFactory::getViewportStateCreateInfo(viewport, scissor);

	VkPipelineRasterizationStateCreateInfo rasterizer = PipelineFactory::getRasterizationStateCreateInfo();
	VkPipelineMultisampleStateCreateInfo multisampling = PipelineFactory::getMultisampleStateCreateInfo();

	VkPipelineColorBlendAttachmentState colorBlendAttachment = PipelineFactory::getColorBlendAttachment();
	VkPipelineColorBlendStateCreateInfo colorBlending = PipelineFactory::getColorBlendStateCreateInfo(colorBlendAttachment);

	VkDynamicState dynamicStates[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_LINE_WIDTH
	};

	VkPipelineDynamicStateCreateInfo dynamicState = PipelineFactory::getDynamicStateCreateInfo(dynamicStates);

	VkPipelineDepthStencilStateCreateInfo depthStencil = PipelineFactory::getDepthStencilStateCreateInfo();

	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = stages.size();
	pipelineInfo.pStages = shaderStages;

	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = nullptr; // Optional

	pipelineInfo.layout = _pipelineLayout;
	pipelineInfo.renderPass = _renderPass;
	pipelineInfo.subpass = 0;

	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	if (vkCreateGraphicsPipelines(DeviceHandler::getInstance()->getLogicalDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &this->_pipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}
	else {
		std::cout << "created graphics pipeline!" << std::endl;
	}
}

ShaderPass::~ShaderPass() {
	delete _descriptor;

	vkDestroyPipeline(DeviceHandler::getInstance()->getLogicalDevice(), this->_pipeline, nullptr);
	vkDestroyPipelineLayout(DeviceHandler::getInstance()->getLogicalDevice(), this->_pipelineLayout, nullptr);
}