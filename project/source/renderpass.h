
#ifndef RENDERPASS_CLASS
#define RENDERPASS_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"

#include <array>

class RenderPass {
	public:
		RenderPass();
		~RenderPass();

		VkRenderPass getRenderPass();

	private:
		VkRenderPass _renderPass;

		void setup();
};

#endif