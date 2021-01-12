#include "vulkanhandler.h"

static VulkanHandler* _instance;

VulkanHandler::VulkanHandler() {}


VulkanHandler* VulkanHandler::getInstance() {
	if (!_instance) {
		_instance = new VulkanHandler();
	}
	return _instance;
}

void VulkanHandler::init() {
    // init window
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    this->_window = glfwCreateWindow(Config::WIDTH, Config::HEIGHT, "PAD-Engine", nullptr, nullptr);

    // check if validation layers ar available
    if (this->_enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    else {
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
    if (vkCreateInstance(&createInfo, nullptr, &_vkInstance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create Vulkan instance!");
    }
    else {
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

    // init surface
    if (glfwCreateWindowSurface(this->_vkInstance, this->_window, nullptr, &this->_surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create Vulkan surface instance!");
    }
    else {
        std::cout << "created Vulkan surface instance!" << std::endl;
    }
}

VkInstance VulkanHandler::getVkInstance() {
    return this->_vkInstance;
}

GLFWwindow* VulkanHandler::getWindow() {
    return this->_window;
}

VkSurfaceKHR VulkanHandler::getSurface() {
    return this->_surface;
}

bool VulkanHandler::checkValidationLayerSupport() {
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

void VulkanHandler::deleteInstance() {
	delete _instance;
	_instance = nullptr;
}

VulkanHandler::~VulkanHandler() {
    vkDestroySurfaceKHR(_vkInstance, this->_surface, nullptr);
    vkDestroyInstance(this->_vkInstance, nullptr);
    glfwDestroyWindow(this->_window);
}