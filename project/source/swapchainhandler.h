
#ifndef SWAPCHAINHANDLER_CLASS
#define SWAPCHAINHANDLER_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "config.h"
#include "devicehandler.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>
#include <vector>
#include <set>

class SwapChainHandler {
public:
	SwapChainHandler(VkInstance _instance, VkSurfaceKHR _surface, DeviceHandler* _deviceHandler);
	~SwapChainHandler();

	void recreate();
	void cleanup();

	void setupSwapChain();
	void setupFramebuffers(VkRenderPass _renderPass);

	// TODO: maby chaing to struct
	VkSwapchainKHR getSwapChain();
	std::vector<VkImage> getSwapChainImages();
	VkFormat getSwapChainImageFormat();
	VkExtent2D getSwapChainExtent();
	std::vector<VkFramebuffer> getSwapChainFramebuffers();

private:
	
	VkInstance _instance;
	VkSurfaceKHR _surface;
	DeviceHandler* _deviceHandler;
	VkPhysicalDevice _physicalDevice;
	VkDevice _device;

	VkSwapchainKHR _swapChain;
	std::vector<VkImage> _swapChainImages;
	VkFormat _swapChainImageFormat;
	VkExtent2D _swapChainExtent;

	std::vector<VkImageView> _swapChainImageViews;
	std::vector<VkFramebuffer> _swapChainFramebuffers;

	void createSwapChain();
	void createImageView();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities);
};
#endif