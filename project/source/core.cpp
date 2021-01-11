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
    this->createSurface();

	DeviceHandler::getInstance()->init(this->_instance, this->_surface);
    SwapChainHandler::getInstance()->init(this->_instance, this->_surface);

    _renderer = new Renderer(_instance, _window);
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

void Core::createSurface() {
    if (glfwCreateWindowSurface(this->_instance, this->_window, nullptr, &this->_surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create Vulkan surface instance!");
    }
    else {
        std::cout << "created Vulkan surface instance!" << std::endl;
    }
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

void Core::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    this->_window = glfwCreateWindow(Config::WIDTH, Config::HEIGHT, "PAD-Engine", nullptr, nullptr);
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, framebufferResizeCallback);
    //glfwSetWindowSizeCallback(_window, framebufferResizeCallback);
}

void Core::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<Core*>(glfwGetWindowUserPointer(window));
    app->_renderer->setFramebufferResized();
}

void Core::loop() {
    while (!glfwWindowShouldClose(this->_window)) {
        glfwPollEvents();
        _renderer->draw();
    }

    vkDeviceWaitIdle(DeviceHandler::getInstance()->getLogicalDevice());
}

void Core::cleanup() {
    delete _renderer;
    SwapChainHandler::deleteInstance();
	DeviceHandler::deleteInstance();

    vkDestroySurfaceKHR(this->_instance, this->_surface, nullptr);
    vkDestroyInstance(this->_instance, nullptr);

    glfwDestroyWindow(_window);

    glfwTerminate();
}
