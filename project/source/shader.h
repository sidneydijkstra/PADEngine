
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

#include <iostream>
#include <vector>
#include <string>

class Shader {
public:
	Shader(VkInstance _instance, DeviceHandler* _deviceHandler, SwapChainHandler* _swapChainHandler, std::string _vertexPath, std::string _fragmentPath);
	~Shader();

	VkRenderPass getRenderPass();
	VkPipelineLayout getPipelineLayout();
	VkPipeline getGraphicsPipeline();

private:
	VkInstance _instance;
	DeviceHandler* _deviceHandler;
	SwapChainHandler* _swapChainHandler;

	void setupRenderPass();
	void setupGraphicsPipeline(std::string _vertexPath, std::string _fragmentPath);

	std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkRenderPass _renderPass;
	VkPipelineLayout _pipelineLayout;
	VkPipeline _graphicsPipeline;
};
#endif