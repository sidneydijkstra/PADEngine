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

    _renderer = new Renderer();

    loop();
    cleanup();
}

void Core::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<Core*>(glfwGetWindowUserPointer(window));
    app->_renderer->setFramebufferResized();
}

void Core::loop() {
    while (!glfwWindowShouldClose(VulkanHandler::getInstance()->getWindow())) {
        glfwPollEvents();
        _renderer->draw();
    }

    vkDeviceWaitIdle(DeviceHandler::getInstance()->getLogicalDevice());
}

void Core::cleanup() {
    delete _renderer;
    SwapChainHandler::deleteInstance();
	DeviceHandler::deleteInstance();
    VulkanHandler::deleteInstance();

    glfwTerminate();
}
