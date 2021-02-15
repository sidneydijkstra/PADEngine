/// @file renderpass.h
/// @brief Standalone header providing RenderPass functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef RENDERPASS_CLASS
#define RENDERPASS_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"

#include <array>

namespace pad {

/// @brief Class describing a RenderPass object, which stores the VkRenderPass.
///
/// For the creation and initialization of the Shader within Vulkan a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkRenderPass.html">VkRenderPass</a> is needed. 
/// In this <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkRenderPass.html">VkRenderPass</a> the different attachments that will be used inside the Shader can be found. 
/// Examples of the attachments are a DepthBuffer and SampleBuffer. Before these attachments can be used, they will need to be indicated to the RenderPass.

class RenderPass {
	public:
		/// @brief The constructor for the RenderPass class.
		RenderPass();
		/// @brief The deconstructor for the RenderPass class.
		~RenderPass();

		/// @bried Get the VkRenderPass object.
		/// @return VkRenderPass object;
		VkRenderPass getRenderPass();

	private:
		VkRenderPass _renderPass; ///< @brief VkRenderPass object of RenderPass.

		/// @bried Setup the VkRenderPass.
		void setup();
};

}

#endif