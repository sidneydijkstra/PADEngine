
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

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class DeviceHandler {
	public:
		DeviceHandler();
		~DeviceHandler();

		static DeviceHandler* getInstance();
		static void deleteInstance();
		void init();

		VkPhysicalDevice getPhysicalDevice();
		VkDevice getLogicalDevice();
		VkQueue getDevicePresentQueue();
		VkQueue getDeviceGraphicsQueue();
		VkCommandPool getCommandPool();

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice _device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice _device);


		VkFormat findDepthFormat();
		bool hasStencilComponent(VkFormat _format);
	private:
		VkPhysicalDevice _physicalDevice;
		VkDevice _logicaldevice;

		VkQueue _presentQueue;
		VkQueue _graphicsQueue;

		VkCommandPool _commandPool;

		void pickPhysicalDevice();
		void createLogicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice _device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice _device);

		void setupCommandPool();

		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

		// add device extensions
		const std::vector<const char*> _deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
};
#endif