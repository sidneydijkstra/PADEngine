#include "devicehandler.h"

static DeviceHandler* _instance;

DeviceHandler::DeviceHandler() {}

DeviceHandler * DeviceHandler::getInstance() {
	if (!_instance) {
		_instance = new DeviceHandler();
	}
	return _instance;
}

void DeviceHandler::deleteInstance() {
	delete _instance;
	_instance = nullptr;
}

void DeviceHandler::init(VkInstance _instance, VkSurfaceKHR _surface) {
	this->_vulkanInstance = _instance;
	this->_surface = _surface;
	this->pickPhysicalDevice();
	this->createLogicalDevice();

	QueueFamilyIndices indices = findQueueFamilies(this->_physicalDevice);
	vkGetDeviceQueue(this->_logicaldevice, indices.presentFamily.value(), 0, &_presentQueue);
	indices = findQueueFamilies(this->_physicalDevice);
	vkGetDeviceQueue(this->_logicaldevice, indices.graphicsFamily.value(), 0, &_graphicsQueue);

	this->setupCommandPool();
}

VkPhysicalDevice DeviceHandler::getPhysicalDevice() {
	return this->_physicalDevice;
}

VkDevice DeviceHandler::getLogicalDevice() {
	return this->_logicaldevice;
}

VkQueue DeviceHandler::getDevicePresentQueue() {
	return this->_presentQueue;
}

VkQueue DeviceHandler::getDeviceGraphicsQueue() {
	return this->_graphicsQueue;
}

VkCommandPool DeviceHandler::getCommandPool() {
	return this->_commandPool;
}

void DeviceHandler::pickPhysicalDevice() {
	this->_physicalDevice = VK_NULL_HANDLE;

	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(this->_vulkanInstance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	else {
		std::cout << "found GPUs with Vulkan support!" << std::endl;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(this->_vulkanInstance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			this->_physicalDevice = device;
			break;
		}
	}

	if (this->_physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
	else {
		std::cout << "found suitable GPU!" << std::endl;
	}
}

void DeviceHandler::createLogicalDevice() {
	QueueFamilyIndices indices = findQueueFamilies(this->_physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(this->_deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = this->_deviceExtensions.data();

	if (vkCreateDevice(this->_physicalDevice, &createInfo, nullptr, &this->_logicaldevice) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}
	else {
		std::cout << "created logical device!" << std::endl;
	}
}

bool DeviceHandler::isDeviceSuitable(VkPhysicalDevice _device) {
	QueueFamilyIndices indices = findQueueFamilies(_device);

	bool extensionsSupported = checkDeviceExtensionSupport(_device);

	bool swapChainAdequate = false;
	if (extensionsSupported) {
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(_device);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	VkPhysicalDeviceFeatures supportedFeatures;
	vkGetPhysicalDeviceFeatures(_device, &supportedFeatures);

	return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

bool DeviceHandler::checkDeviceExtensionSupport(VkPhysicalDevice _device) {
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(_device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(_device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(this->_deviceExtensions.begin(), this->_deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

VkFormat DeviceHandler::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
	for (VkFormat format : candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(this->getPhysicalDevice(), format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}

	throw std::runtime_error("failed to find supported format!");
}

bool DeviceHandler::hasStencilComponent(VkFormat _format) {
	return _format == VK_FORMAT_D32_SFLOAT_S8_UINT || _format == VK_FORMAT_D24_UNORM_S8_UINT;
}

QueueFamilyIndices DeviceHandler::findQueueFamilies(VkPhysicalDevice _device) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(_device, i, this->_surface, &presentSupport);

		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

SwapChainSupportDetails DeviceHandler::querySwapChainSupport(VkPhysicalDevice _device) {
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device, this->_surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(_device, this->_surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(_device, this->_surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(_device, this->_surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_device, this->_surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

void DeviceHandler::setupCommandPool() {
	QueueFamilyIndices queueFamilyIndices = findQueueFamilies(_physicalDevice);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
	poolInfo.flags = 0; // Optional

	if (vkCreateCommandPool(_logicaldevice, &poolInfo, nullptr, &this->_commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}
	else {
		std::cout << "created command pool!" << std::endl;
	}
}

VkFormat DeviceHandler::findDepthFormat() {
	return findSupportedFormat(
		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}


DeviceHandler::~DeviceHandler() {
	vkDestroyCommandPool(this->_logicaldevice , this->_commandPool, nullptr);
	vkDestroyDevice(this->_logicaldevice, nullptr);
}
