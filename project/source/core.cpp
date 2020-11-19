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

	_deviceHandler = new DeviceHandler(this->_instance, this->_surface);

	_deviceHandler->setupDevices();

	this->_physicalDevice = _deviceHandler->getPhysicalDevice();
	this->_device = _deviceHandler->getLogicalDevice();

	_deviceHandler->getDevicePresentQueue(_presentQueue);
	_deviceHandler->getDeviceGraphicsQueue(_graphicsQueue);

    //this->pickPhysicalDevice();
    //this->createLogicalDevice();

    _swapChainHandler = new SwapChainHandler(this->_instance, this->_surface, _deviceHandler);

    _swapChainHandler->setupSwapChain();
    this->_swapChain = _swapChainHandler->getSwapChain();

    //this->createSwapChain();
    //this->createImageView();

	_shader = new Shader(this->_instance, this->_deviceHandler, this->_swapChainHandler, "shaders/vert.spv", "shaders/frag.spv");

    //this->createRenderPass();
	//this->createGraphicsPipeline();

    _swapChainHandler->setupFramebuffers(_shader->getRenderPass());

    //this->createFramebuffers();
    this->createCommandPool();
    this->createCommandBuffers();
    this->createSyncObjects();
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

void Core::createCommandPool() {
    QueueFamilyIndices queueFamilyIndices = _deviceHandler->findQueueFamilies(this->_physicalDevice);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    poolInfo.flags = 0; // Optional

    if (vkCreateCommandPool(this->_device, &poolInfo, nullptr, &this->_commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }else {
        std::cout << "created command pool!" << std::endl;
    }
}


void Core::createCommandBuffers() {
    this->_commandBuffers.resize(this->_swapChainHandler->getSwapChainFramebuffers().size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = this->_commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)this->_commandBuffers.size();

    if (vkAllocateCommandBuffers(this->_device, &allocInfo, this->_commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }else {
        std::cout << "created command buffers!" << std::endl;
    }

    for (size_t i = 0; i < this->_commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        if (vkBeginCommandBuffer(this->_commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }else {
            std::cout << "\t- begin recording command buffer!" << std::endl;
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = this->_shader->getRenderPass();
        renderPassInfo.framebuffer = this->_swapChainHandler->getSwapChainFramebuffers()[i];

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = this->_swapChainHandler->getSwapChainExtent();

        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(this->_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(this->_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, this->_shader->getGraphicsPipeline());
        vkCmdDraw(this->_commandBuffers[i], 3, 1, 0, 0);
        vkCmdEndRenderPass(this->_commandBuffers[i]);

        if (vkEndCommandBuffer(this->_commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }else {
            std::cout << "\t- recording command buffer!" << std::endl;
        }
    }
}

void Core::createSyncObjects() {
    this->_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    this->_imagesInFlight.resize(this->_swapChainHandler->getSwapChainImages().size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(this->_device, &semaphoreInfo, nullptr, &this->_imageAvailableSemaphores[i]) != VK_SUCCESS || vkCreateSemaphore(this->_device, &semaphoreInfo, nullptr, &this->_renderFinishedSemaphores[i]) != VK_SUCCESS || vkCreateFence(this->_device, &fenceInfo, nullptr, &this->_inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }else {
            std::cout << "\t- created synchronization object for a frame!" << std::endl;
        }
    }
}

void Core::drawFrame() {
    vkWaitForFences(this->_device, 1, &this->_inFlightFences[this->_currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(this->_device, this->_swapChain, UINT64_MAX, this->_imageAvailableSemaphores[this->_currentFrame], VK_NULL_HANDLE, &imageIndex);

    // Check if a previous frame is using this image (i.e. there is its fence to wait on)
    if (imageIndex == UINT64_MAX || this->_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(this->_device, 1, &this->_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    // Mark the image as now being in use by this frame
    this->_imagesInFlight[imageIndex] = this->_inFlightFences[this->_currentFrame];

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { this->_imageAvailableSemaphores[this->_currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &this->_commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = { this->_renderFinishedSemaphores[this->_currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(this->_device, 1, &this->_inFlightFences[this->_currentFrame]);

    if (vkQueueSubmit(this->_graphicsQueue, 1, &submitInfo, this->_inFlightFences[this->_currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { this->_swapChain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    this->_currentFrame = (this->_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

    vkQueuePresentKHR(this->_presentQueue, &presentInfo);
    vkQueueWaitIdle(this->_presentQueue);
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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->_window = glfwCreateWindow(Config::WIDTH, Config::HEIGHT, "PAD-Engine", nullptr, nullptr);
}

void Core::loop() {
    while (!glfwWindowShouldClose(this->_window)) {
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(this->_device);
}

void Core::cleanup() {
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(this->_device, this->_renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(this->_device, this->_imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(this->_device, this->_inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(this->_device, this->_commandPool, nullptr);
    
	delete _shader;
    delete _swapChainHandler;
    delete _deviceHandler;

    vkDestroySurfaceKHR(this->_instance, this->_surface, nullptr);
    vkDestroyInstance(this->_instance, nullptr);

    glfwDestroyWindow(_window);

    glfwTerminate();
}
