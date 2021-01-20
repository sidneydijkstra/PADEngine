
#ifndef SHADERSTAGE_CLASS
#define SHADERSTAGE_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"
#include "vertex.h"

#include <iostream>
#include <vector>
#include <string>

class ShaderStage {
	public:
		ShaderStage(const char* _path, VkShaderStageFlagBits _stage);
		~ShaderStage();

		VkPipelineShaderStageCreateInfo getStateInfo();

	private:
		std::vector<char> _shaderCode;
		VkShaderModule _shaderModule;
		VkPipelineShaderStageCreateInfo _stageInfo;

		std::vector<char> readFile(const std::string& _filename);
		VkShaderModule createShaderModule(const std::vector<char>& _code);
};

#endif