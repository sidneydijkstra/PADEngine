
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


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
		void init(VkInstance _instance, VkSurfaceKHR _surface);

		VkPhysicalDevice getPhysicalDevice();
		VkDevice getLogicalDevice();

		// TODO: might not need this, we can get QueueFamilyIndices from findQueueFamilies();
		VkQueue getDevicePresentQueue();
		VkQueue getDeviceGraphicsQueue();

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice _device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice _device);

		VkFormat findDepthFormat();
		bool hasStencilComponent(VkFormat _format);
	private:
		// add device extensions
		const std::vector<const char*> _deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		VkInstance _vulkanInstance;
		VkSurfaceKHR _surface;

		VkPhysicalDevice _physicalDevice;
		VkDevice _logicaldevice;

		VkQueue _presentQueue;
		VkQueue _graphicsQueue;

		void pickPhysicalDevice();
		void createLogicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice _device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice _device);

		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
};
#endif