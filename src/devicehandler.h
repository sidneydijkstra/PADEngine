/// @file devicehandler.h
/// @brief Standalone header providing DeviceHandler functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "vulkanhandler.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>
#include <vector>
#include <set>

#ifndef DEVICEHANDLER_CLASS
#define DEVICEHANDLER_CLASS

/// @brief Struct describing QueueFamilyIndices data object, which contains information about the graphics card.
struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();;
	}
};

/// @brief Struct describing SwapChainSupportDetails data object, which contains information about the surface and present modes.
struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

/// @brief Class describing a DeviceHandler object, which is used to setup the device (graphics card) and handle the configuration/support.
class DeviceHandler {
	public:
		/// @brief The constructor for the DeviceHandler class.
		DeviceHandler();
		/// @brief The deconstructor for the DeviceHandler class.
		~DeviceHandler();

		/// @brief Static get instance function, DeviceHandler is a singelton because we only need one instance.
		/// @return A pointer to DeviceHandler.
		static DeviceHandler* getInstance();

		/// @brief Static function to delete and cleanup the DeviceHandler.
		static void deleteInstance();

		/// @brief Initialisation function for DeviceHandler.
		void init();

		/// @brief Get current physical device.
		/// @return A reference to VkPhysicalDevice.
		VkPhysicalDevice getPhysicalDevice();

		/// @brief Get current logical device.
		/// @return A reference to VkDevice.
		VkDevice getLogicalDevice();

		/// @brief Get current present queue.
		/// @return A reference to VkQueue.
		VkQueue getDevicePresentQueue();

		/// @brief Get current graphics queue.
		/// @return A reference to VkQueue.
		VkQueue getDeviceGraphicsQueue();

		/// @brief Get current command pool.
		/// @return A reference to VkCommandPool.
		VkCommandPool getCommandPool();

		/// @brief Get current msaa samples flag bit.
		/// @return A reference to VkSampleCountFlagBits.
		VkSampleCountFlagBits getMsaaSamples();

		/// @brief Find the QueueFamilyIndices and return a reference.
		/// @param _device A VkPhysicalDevice.
		/// @return A reference to QueueFamilyIndices.
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice _device);

		/// @brief Find the SwapChainSupportDetails and return a reference.
		/// @param _device A VkPhysicalDevice.
		/// @return A reference to SwapChainSupportDetails.
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice _device);

		/// @brief Find the depth format and return a reference.
		/// @return A reference to VkFormat.
		VkFormat findDepthFormat();

		/// @brief Check if a VkFormat has a stencil component.
		/// @return A boolean containing stencil component case.
		bool hasStencilComponent(VkFormat _format);

	private:
		VkPhysicalDevice _physicalDevice; ///< @brief VkPhysicalDevice object containing physical device.
		VkDevice _logicaldevice; ///< @brief VkDevice object containing logical device.

		VkQueue _presentQueue; ///< @brief VkQueue object containing present queue.
		VkQueue _graphicsQueue; ///< @brief VkQueue object containing graphics queue.

		VkCommandPool _commandPool; ///< @brief VkCommandPool object containing current command pool.
		VkSampleCountFlagBits _msaaSamples; ///< @brief VkSampleCountFlagBits object containing sample count.

		/// @brief Pick a physical device.
		void pickPhysicalDevice();

		/// @brief Pick a logical device.
		void createLogicalDevice();

		/// @brief Check if device is a suitable.
		/// @param _device Device to do check on.
		/// @return A boolean containing Suitable device case.
		bool isDeviceSuitable(VkPhysicalDevice _device);

		/// @brief Check if device has extension support.
		/// @param _device Device to do check on.
		/// @return A boolean containing device has extension support case.
		bool checkDeviceExtensionSupport(VkPhysicalDevice _device);

		/// @brief Setup the command pool.
		void setupCommandPool();

		/// @brief Find the support format.
		/// @param candidates Format candidates.
		/// @param tiling Tiling of image.
		/// @param features VkFormatFeatureFlags of image.
		/// @return A supported VkFormat.
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

		/// @brief Get the VkSampleCountFlagBits.
		/// @return A VkSampleCountFlagBits.
		VkSampleCountFlagBits getMaxUsableSampleCount();

		// add device extensions
		const std::vector<const char*> _deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
};

#endif