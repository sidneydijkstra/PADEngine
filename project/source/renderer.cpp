#include "renderer.h"

Renderer::Renderer(VkInstance _instance, DeviceHandler* _deviceHandler, SwapChainHandler* _swapChainHandler, GLFWwindow* _window) {
	this->_instance = _instance;
	this->_deviceHandler = _deviceHandler;
	this->_swapChainHandler = _swapChainHandler;
    this->_window = _window;

    this->_shader = new Shader(this->_instance, this->_deviceHandler, this->_swapChainHandler, "shaders/vert.spv", "shaders/frag.spv");

    this->_swapChainHandler->setupFramebuffers(_shader->getRenderPass());

    this->_deviceHandler->getDevicePresentQueue(_presentQueue);
    this->_deviceHandler->getDeviceGraphicsQueue(_graphicsQueue);

    this->setupCommandPool();

    _buffer = new Buffer(this->_instance, this->_deviceHandler, this->_shader, _graphicsQueue, _commandPool, this->_swapChainHandler->getSwapChainImages().size());

    this->setupCommandBuffers();
    this->setupSyncObjects();
}

void Renderer::recreate() {
    int width = 0, height = 0;
    glfwGetFramebufferSize(_window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(_window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(this->_deviceHandler->getLogicalDevice());

    this->cleanup();
    this->_swapChainHandler->recreate();
    delete _shader;
    this->_shader = new Shader(this->_instance, this->_deviceHandler, this->_swapChainHandler, "shaders/vert.spv", "shaders/frag.spv");
    this->_swapChainHandler->setupFramebuffers(_shader->getRenderPass());
    delete _buffer;
    _buffer = new Buffer(this->_instance, this->_deviceHandler, this->_shader, _graphicsQueue, _commandPool, this->_swapChainHandler->getSwapChainImages().size());
    this->setupCommandBuffers();
}

void Renderer::cleanup() {
    vkFreeCommandBuffers(this->_deviceHandler->getLogicalDevice(), _commandPool, static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());
}

void Renderer::update(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    ubo.proj = glm::perspective(glm::radians(45.0f), this->_swapChainHandler->getSwapChainExtent().width / (float)this->_swapChainHandler->getSwapChainExtent().height, 0.1f, 10.0f);

    ubo.proj[1][1] *= -1;

    _buffer->updateUniformBuffers(currentImage, ubo);
}

void Renderer::setupCommandPool() {
    QueueFamilyIndices queueFamilyIndices = _deviceHandler->findQueueFamilies(this->_deviceHandler->getPhysicalDevice());

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    poolInfo.flags = 0; // Optional

    if (vkCreateCommandPool(this->_deviceHandler->getLogicalDevice(), &poolInfo, nullptr, &this->_commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
    else {
        std::cout << "created command pool!" << std::endl;
    }
}

void Renderer::setupCommandBuffers() {
    this->_commandBuffers.resize(this->_swapChainHandler->getSwapChainFramebuffers().size());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = this->_commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)this->_commandBuffers.size();

    if (vkAllocateCommandBuffers(this->_deviceHandler->getLogicalDevice(), &allocInfo, this->_commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
    else {
        std::cout << "created command buffers!" << std::endl;
    }

    for (size_t i = 0; i < this->_commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        if (vkBeginCommandBuffer(this->_commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }
        else {
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

        BufferData vertexData = _buffer->getVertexBuffer();
        BufferData indexData = _buffer->getIndexBuffer();

        VkBuffer vertexBuffers[] = { vertexData.buffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(this->_commandBuffers[i], 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(this->_commandBuffers[i], indexData.buffer, 0, VK_INDEX_TYPE_UINT16);

        vkCmdBindDescriptorSets(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _shader->getPipelineLayout(), 0, 1, &_buffer->getDescriptorSets()[i], 0, nullptr);
        vkCmdDrawIndexed(_commandBuffers[i], static_cast<uint32_t>(indexData.size), 1, 0, 0, 0);
        vkCmdEndRenderPass(this->_commandBuffers[i]);

        if (vkEndCommandBuffer(this->_commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
        else {
            std::cout << "\t- recording command buffer!" << std::endl;
        }
    }
}

void Renderer::setupSyncObjects() {
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
        if (vkCreateSemaphore(this->_deviceHandler->getLogicalDevice(), &semaphoreInfo, nullptr, &this->_imageAvailableSemaphores[i]) != VK_SUCCESS || vkCreateSemaphore(this->_deviceHandler->getLogicalDevice(), &semaphoreInfo, nullptr, &this->_renderFinishedSemaphores[i]) != VK_SUCCESS || vkCreateFence(this->_deviceHandler->getLogicalDevice(), &fenceInfo, nullptr, &this->_inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
        else {
            std::cout << "\t- created synchronization object for a frame!" << std::endl;
        }
    }
}

void Renderer::draw() {
    vkWaitForFences(this->_deviceHandler->getLogicalDevice(), 1, &this->_inFlightFences[this->_currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(this->_deviceHandler->getLogicalDevice(), this->_swapChainHandler->getSwapChain(), UINT64_MAX, this->_imageAvailableSemaphores[this->_currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        this->recreate();
        return;
    }else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    // Check if a previous frame is using this image (i.e. there is its fence to wait on)
    if (imageIndex == UINT64_MAX || this->_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(this->_deviceHandler->getLogicalDevice(), 1, &this->_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    // Mark the image as now being in use by this frame
    this->_imagesInFlight[imageIndex] = this->_inFlightFences[this->_currentFrame];

    update(imageIndex);

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

    vkResetFences(this->_deviceHandler->getLogicalDevice(), 1, &this->_inFlightFences[this->_currentFrame]);

    if (vkQueueSubmit(this->_graphicsQueue, 1, &submitInfo, this->_inFlightFences[this->_currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { this->_swapChainHandler->getSwapChain() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    result = vkQueuePresentKHR(_presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _framebufferResized) {
        this->_framebufferResized = false;
        this->recreate();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    this->_currentFrame = (this->_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

    vkQueueWaitIdle(this->_presentQueue);
}

void Renderer::setFramebufferResized() {
    this->_framebufferResized = true;
}

Renderer::~Renderer() {
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(this->_deviceHandler->getLogicalDevice(), this->_renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(this->_deviceHandler->getLogicalDevice(), this->_imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(this->_deviceHandler->getLogicalDevice(), this->_inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(this->_deviceHandler->getLogicalDevice(), this->_commandPool, nullptr);

    delete _buffer;
    delete _shader;
}

