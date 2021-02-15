/// @file swapchainhandler.h
/// @brief Standalone header providing SwapChainHandler functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

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

/// @brief Class describing a SwapChainHandler object, which handles all the swapchain logic.
///
/// The SwapChainHandler class is in its essence a class that contains a list of images on which can be renderd. 
/// In Vulkan there is the option to render the next frame in advance. Which means that when the currentframe is rendering the engine calculates the next frame, there for there are multiple frames needed in advance. 
/// For this purpose, the class contains a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkSwapchainKHR.html">VkSwapchainKHR</a> which is a list of <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkImage.html">VkImages</a> which are the images on which is drawn. 
/// Lastly the information needed for the SwapChain are stored in a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkFormat.html">VkFormat</a> and a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkExtent2D.html">VkExtent2D</a> objects.

class SwapChainHandler {
public:
	/// @brief The constructor for the SwapChainHandler class.
	SwapChainHandler();
	/// @brief The deconstructor for the SwapChainHandler class.
	~SwapChainHandler();

	/// @brief Static get instance function, SwapChainHandler is a singelton because we only need one instance.
	/// @return A pointer to SwapChainHandler.
	static SwapChainHandler* getInstance();

	/// @brief Static function to delete and cleanup the SwapChainHandler.
	static void deleteInstance();

	/// @brief Initialisation function for SwapChainHandler.
	void init();

	/// @brief Recreate function for SwapChainHandler.
	void recreate();

	/// @brief Get the swapchain.
	/// @return The VkSwapchainKHR.
	VkSwapchainKHR getSwapChain();

	/// @brief Get the swapchain images.
	/// @return A std::vector of VkImage.
	std::vector<VkImage> getSwapChainImages();

	/// @brief Get the swapchain images views.
	/// @return A std::vector of VkImageView.
	std::vector<VkImageView> getSwapChainImageViews();

	/// @brief Get the swapchain image size.
	/// @return The swapchain image size.
	int getSwapChainImagesSize();

	/// @brief Get the swapchain image format.
	/// @return The VkFormat.
	VkFormat getSwapChainImageFormat();

	/// @brief Get the swapchain extent.
	/// @return The VkExtent2D.
	VkExtent2D getSwapChainExtent();

	/// @brief Get the swapchain width.
	/// @return The width of swapchain.
	int getSwapChainWidth();

	/// @brief Get the swapchain height.
	/// @return The height of swapchain.
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