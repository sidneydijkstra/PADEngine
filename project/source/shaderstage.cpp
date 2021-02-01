#include "shaderstage.h"

ShaderStage::ShaderStage(const char* _path, VkShaderStageFlagBits _stage) {
	this->_shaderCode = readFile(_path);
	this->_shaderModule = createShaderModule(_shaderCode);

	_stageInfo = VkPipelineShaderStageCreateInfo{};
	_stageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	_stageInfo.stage = _stage;
	_stageInfo.module = this->_shaderModule;
	_stageInfo.pName = "main";
}

VkPipelineShaderStageCreateInfo ShaderStage::getStateInfo() {
	return this->_stageInfo;
}

std::vector<char> ShaderStage::readFile(const std::string& _filename) {
	std::ifstream file(_filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

VkShaderModule ShaderStage::createShaderModule(const std::vector<char>& _code) {
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = _code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(_code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(DeviceHandler::getInstance()->getLogicalDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}
	else {
		std::cout << "created shader module!" << std::endl;
	}

	return shaderModule;
}

ShaderStage::~ShaderStage() {
	this->_shaderCode.clear();
	vkDestroyShaderModule(DeviceHandler::getInstance()->getLogicalDevice(), this->_shaderModule, nullptr);
}
