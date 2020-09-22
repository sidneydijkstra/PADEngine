#include "core.h"

Core::Core() {

}

Core::~Core() {

}

void Core::run() {
    initWindow();
    initVulkan();
    loop();
    cleanup();
}

void Core::initVulkan() {
    this->createInstance();
    this->pickPhysicalDevice();
    this->createLogicalDevice();
}

void Core::createInstance() {
    // check if validation layers ar available
    if (this->_enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }else {
        std::cout << "validation layers requested and available!" << std::endl;
    }

    // create struck with information about vulkan, technically optional but it may provide some useful information to the driver in order to optimize our specific application
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "PADEngine";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "No Engine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_0;

    // tell the Vulkan driver which global extensions and validation layers we want to use
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    
    // add validation layers
    if (this->_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(this->_validationLayers.size());
        createInfo.ppEnabledLayerNames = this->_validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    // create a vulkan instance
    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create Vulkan instance!");
    }else {
        std::cout << "created Vulkan instance!" << std::endl;
    }

    // check available vulkan extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // print available extensions
    /*std::cout << "available extensions:\n";

    for (const auto& extension : extensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }*/
}

bool Core::checkValidationLayerSupport() {
    // get all validation layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // check if all the layers in _validationLayers exist in availableLayers
    for (const char* layerName : this->_validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

bool Core::isDeviceSuitable(VkPhysicalDevice _device) {
    QueueFamilyIndices indices = findQueueFamilies(_device);
    return indices.isComplete();
}

QueueFamilyIndices Core::findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

void Core::pickPhysicalDevice() {
    this->_physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(this->_instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }else {
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
    }else {
        std::cout << "found suitable GPU!" << std::endl;
    }
}

void Core::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(this->_physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;

    // not needed in nieuwer versions of vulkan but good for compatability
    createInfo.enabledExtensionCount = 0;
    if (this->_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(this->_validationLayers.size());
        createInfo.ppEnabledLayerNames = this->_validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(this->_physicalDevice, &createInfo, nullptr, &this->_device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }else {
        std::cout << "created logical device!" << std::endl;
    }
    vkGetDeviceQueue(this->_device, indices.graphicsFamily.value(), 0, &this->_graphicsQueue);
}

void Core::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->_window = glfwCreateWindow(this->WIDTH, this->HEIGHT, "PAD-Engine", nullptr, nullptr);
}

void Core::loop() {
    while (!glfwWindowShouldClose(this->_window)) {
        glfwPollEvents();
    }
}

void Core::cleanup() {
    vkDestroyDevice(this->_device, nullptr);
    vkDestroyInstance(this->_instance, nullptr);

    glfwDestroyWindow(_window);

    glfwTerminate();
}
