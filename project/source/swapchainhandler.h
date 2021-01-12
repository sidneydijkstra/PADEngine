
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
#include "vulkanhandler.h"
#include "devicehandler.h"
#include "depthbuffer.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>
#include <array>
#include <vector>
#include <set>

class SwapChainHandler {
public:
	SwapChainHandler();
	~SwapChainHandler();

	static SwapChainHandler* getInstance();
	static void deleteInstance();
	void init();

	void recreate();

	// TODO: maby chaing to struct
	VkSwapchainKHR getSwapChain();
	std::vector<VkImage> getSwapChainImages();
	std::vector<VkImageView> getSwapChainImageViews();
	int getSwapChainImagesSize();
	VkFormat getSwapChainImageFormat();
	VkExtent2D getSwapChainExtent();
	int getSwapChainWidth();
	int getSwapChainHeight();

private:
	VkSwapchainKHR _swapChain;
	std::vector<VkImage> _swapChainImages;
	VkFormat _swapChainImageFormat;
	VkExtent2D _swapChainExtent;

	std::vector<VkImageView> _swapChainImageViews;

	void cleanup();
	void setupSwapChain();
	void createSwapChain();
	void createImageView();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities);
};
#endif