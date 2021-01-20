
#ifndef SHADEREFFECT_CLASS
#define SHADEREFFECT_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"
#include "resourcemanager.h"
#include "shadermanager.h"
#include "descriptor.h"
#include "vertex.h"

#include "shaderstage.h"

#include <iostream>
#include <vector>
#include <string>

class ShaderEffect {
	public:
		ShaderEffect(const char* _vertexPath, const char* _fragmentPath);
		~ShaderEffect();

		std::vector<ShaderStage*> getStages();

	protected:
		std::vector<ShaderStage*> _stages;
};

#endif