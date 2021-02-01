#include "core.h"

Core::Core() {
    // init vulkan / window / surface
    VulkanHandler::getInstance()->init();

    // setup window options / callbacks
    glfwSetWindowUserPointer(VulkanHandler::getInstance()->getWindow(), this);
    glfwSetFramebufferSizeCallback(VulkanHandler::getInstance()->getWindow(), framebufferResizeCallback);

    DeviceHandler::getInstance()->init();
    SwapChainHandler::getInstance()->init();
    Input::attachToWindow(VulkanHandler::getInstance()->getWindow());

    _seqManager = new SequenceManager();
}

void Core::run() {
    try {
        this->_run();
    }
    catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return;
    }
}

void Core::_run() {
    loop();
}

void Core::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<Core*>(glfwGetWindowUserPointer(window));
    app->_seqManager->setFramebufferResized();
}

void Core::loop() {
    while (!glfwWindowShouldClose(VulkanHandler::getInstance()->getWindow())) {
        Input::update();
        Time::update();

        Scene* scene = SceneManager::getInstance()->getCurrentScene();
        if(scene != nullptr)
            _seqManager->draw(scene);
    }

    vkDeviceWaitIdle(DeviceHandler::getInstance()->getLogicalDevice());
}

void Core::cleanup() {
    delete _seqManager;

    MaterialManager::deleteInstance();
    ShaderManager::deleteInsance();
    ResourceManager::deleteInstance();
    SwapChainHandler::deleteInstance();
	DeviceHandler::deleteInstance();
    VulkanHandler::deleteInstance();

    glfwTerminate();
}

Core::~Core() {

}
