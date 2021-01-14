#include "core.h"

Core::Core() {

}

Core::~Core() {

}

void Core::run() {
    // init vulkan / window / surface
    VulkanHandler::getInstance()->init();

    // setup window options / callbacks
    glfwSetWindowUserPointer(VulkanHandler::getInstance()->getWindow(), this);
    glfwSetFramebufferSizeCallback(VulkanHandler::getInstance()->getWindow(), framebufferResizeCallback);

    DeviceHandler::getInstance()->init();
    SwapChainHandler::getInstance()->init();

    _seqManager = new SequenceManager();
    _scene = new Scene();

    loop();
    cleanup();
}

void Core::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<Core*>(glfwGetWindowUserPointer(window));
    app->_seqManager->setFramebufferResized();
}

void Core::loop() {
    while (!glfwWindowShouldClose(VulkanHandler::getInstance()->getWindow())) {
        glfwPollEvents();
        _seqManager->draw(_scene);
    }

    vkDeviceWaitIdle(DeviceHandler::getInstance()->getLogicalDevice());
}

void Core::cleanup() {
    delete _seqManager;
    delete _scene;

    ResourceManager::deleteInstance();
    SwapChainHandler::deleteInstance();
	DeviceHandler::deleteInstance();
    VulkanHandler::deleteInstance();

    glfwTerminate();
}
