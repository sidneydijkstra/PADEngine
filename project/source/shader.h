
#ifndef SHADER_CLASS
#define SHADER_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "devicehandler.h"
#include "swapchainhandler.h"
#include "uniformbuffer.h"
#include "vertex.h"

#include <iostream>
#include <vector>
#include <string>

class Shader {
public:
	Shader(VkInstance _instance, DeviceHandler* _deviceHandler, SwapChainHandler* _swapChainHandler, std::string _vertexPath, std::string _fragmentPath);
	~Shader();

	void setUnifromBuffer(UniformBuffer* _buffer);

	VkRenderPass getRenderPass();
	VkDescriptorSetLayout getDescriptorSetLayout();
	std::vector<VkDescriptorSet> getDescriptiorSets();

	VkPipelineLayout getPipelineLayout();
	VkPipeline getGraphicsPipeline();

private:
	VkInstance _instance;
	DeviceHandler* _deviceHandler;
	SwapChainHandler* _swapChainHandler;

	VkRenderPass _renderPass;
	VkDescriptorSetLayout _descriptorSetLayout;
	VkPipelineLayout _pipelineLayout;
	VkPipeline _graphicsPipeline;

	VkDescriptorPool _descriptorPool;
	std::vector<VkDescriptorSet> _descriptorSets;

	void setupRenderPass();
	void setupDescriptorSetLayout();
	void setupGraphicsPipeline(std::string _vertexPath, std::string _fragmentPath);
	void setupDescriptorPool();
	void setupDescriptorSets(UniformBuffer* _buffer);

	std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);
};
#endif