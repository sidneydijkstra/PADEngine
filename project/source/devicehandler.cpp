#include "devicehandler.h"

DeviceHandler::DeviceHandler(VkInstance _instance, VkSurfaceKHR _surface) {
	this->_instance = _instance;
	this->_surface = _surface;
}


void DeviceHandler::setupDevices() {
	this->pickPhysicalDevice();
	this->createLogicalDevice();
}

VkPhysicalDevice DeviceHandler::getPhysicalDevice() {
	return this->_physicalDevice;
}

VkDevice DeviceHandler::getLogicalDevice() {
	return this->_device;
}

void DeviceHandler::getDevicePresentQueue(VkQueue& _presentQueue) {
	QueueFamilyIndices indices = findQueueFamilies(this->_physicalDevice);
	vkGetDeviceQueue(this->_device, indices.presentFamily.value(), 0, &_presentQueue);
}

void DeviceHandler::getDeviceGraphicsQueue(VkQueue & _graphicsQueue) {
	QueueFamilyIndices indices = findQueueFamilies(this->_physicalDevice);
	vkGetDeviceQueue(this->_device, indices.graphicsFamily.value(), 0, &_graphicsQueue);
}

void DeviceHandler::pickPhysicalDevice() {
	this->_physicalDevice = VK_NULL_HANDLE;

	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(this->_instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	else {
		std::cout << "found GPUs with Vulkan support!" << std::endl;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(this->_instance, &deviceCount, devices.data());

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

	if (vkCreateDevice(this->_physicalDevice, &createInfo, nullptr, &this->_device) != VK_SUCCESS) {
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


DeviceHandler::~DeviceHandler() {
	vkDestroyDevice(this->_device, nullptr);
}