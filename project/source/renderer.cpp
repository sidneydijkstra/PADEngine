#include "renderer.h"

Renderer::Renderer() {
    this->_children = std::vector<Entity*>();

    _children.push_back(new Entity());
    _children.push_back(new Entity());
    _children[1]->pos.x = -1;

    _children[0]->texture()->loadTexture("assets/logo.png");
    _children[1]->texture()->loadTexture("assets/banaan.jpg");

    this->_shader = new Shader("shaders/vert.spv", "shaders/frag.spv", _children[0]->description().descriptorSetLayout);

    _depthBuffer = new DepthBuffer();

    _framebuffers = new FrameBuffers();
    _framebuffers->setupFramebuffers(_shader->getRenderPass(), _depthBuffer);

    this->renderEntitys();
    this->setupSyncObjects();
}

void Renderer::update(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    for (Entity* e : _children) {
        UniformBufferObject ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.model = glm::translate(ubo.model, e->pos);

        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        ubo.proj = glm::perspective(glm::radians(45.0f), SwapChainHandler::getInstance()->getSwapChainExtent().width / (float)SwapChainHandler::getInstance()->getSwapChainExtent().height, 0.1f, 10.0f);

        ubo.proj[1][1] *= -1;

        e->uniform()->updateBuffer(currentImage, ubo);
    }
}

void Renderer::renderEntitys() {
    for (Entity* e : _children) {
        e->recreate();
    }
    setupCommandBuffers(_children[0]);
}

void Renderer::beginCommandBuffer(int _index) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0; // Optional
    beginInfo.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(this->_commandBuffers[_index], &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
    else {
        std::cout << "\t- begin recording command buffer!" << std::endl;
    }
}

void Renderer::endCommandBuffer(int _index) {
    if (vkEndCommandBuffer(this->_commandBuffers[_index]) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
    else {
        std::cout << "\t- recording command buffer!" << std::endl;
    }
}

void Renderer::setupCommandBuffers(Entity* _entity) {
    this->_commandBuffers.resize(_framebuffers->getFrameBuffersSize());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = DeviceHandler::getInstance()->getCommandPool();
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)this->_commandBuffers.size();

    if (vkAllocateCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), &allocInfo, this->_commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
    else {
        std::cout << "created command buffers!" << std::endl;
    }

    for (size_t i = 0; i < this->_commandBuffers.size(); i++) {
        beginCommandBuffer(i);

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = this->_shader->getRenderPass();
        renderPassInfo.framebuffer = _framebuffers->getFrameBuffers()[i];

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = SwapChainHandler::getInstance()->getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
        clearValues[1].depthStencil = { 1.0f, 0 };

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(this->_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(this->_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, this->_shader->getGraphicsPipeline());

        BufferData vertexData = _entity->vertex()->getBuffer();
        BufferData indexData = _entity->index()->getBuffer();

        VkBuffer vertexBuffers[] = { vertexData.buffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(this->_commandBuffers[i], 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(this->_commandBuffers[i], indexData.buffer, 0, VK_INDEX_TYPE_UINT16);
        
        for(Entity* ent : _children){
            vkCmdBindDescriptorSets(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _shader->getPipelineLayout(), 0, 1, & ent->description().descriptorSets[i], 0, nullptr);
            vkCmdDrawIndexed(_commandBuffers[i], static_cast<uint32_t>(indexData.size), 1, 0, 0, 0);
        }

        vkCmdEndRenderPass(this->_commandBuffers[i]);

        endCommandBuffer(i);
    }
}

void Renderer::draw() {
    vkWaitForFences(DeviceHandler::getInstance()->getLogicalDevice(), 1, &this->_inFlightFences[this->_currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(DeviceHandler::getInstance()->getLogicalDevice(), SwapChainHandler::getInstance()->getSwapChain(), UINT64_MAX, this->_imageAvailableSemaphores[this->_currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        this->recreate();
        return;
    }else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    // Check if a previous frame is using this image (i.e. there is its fence to wait on)
    if (imageIndex == UINT64_MAX || this->_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(DeviceHandler::getInstance()->getLogicalDevice(), 1, &this->_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
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

    vkResetFences(DeviceHandler::getInstance()->getLogicalDevice(), 1, &this->_inFlightFences[this->_currentFrame]);

    if (vkQueueSubmit(DeviceHandler::getInstance()->getDeviceGraphicsQueue(), 1, &submitInfo, this->_inFlightFences[this->_currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { SwapChainHandler::getInstance()->getSwapChain() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    result = vkQueuePresentKHR(DeviceHandler::getInstance()->getDevicePresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _framebufferResized) {
        this->_framebufferResized = false;
        this->recreate();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    this->_currentFrame = (this->_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

    vkQueueWaitIdle(DeviceHandler::getInstance()->getDevicePresentQueue());
}

void Renderer::recreate() {
    int width = 0, height = 0;
    glfwGetFramebufferSize(VulkanHandler::getInstance()->getWindow(), &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(VulkanHandler::getInstance()->getWindow(), &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(DeviceHandler::getInstance()->getLogicalDevice());

    this->cleanup();
    SwapChainHandler::getInstance()->recreate();
    delete _shader;
    this->_shader = new Shader("shaders/vert.spv", "shaders/frag.spv", _children[0]->description().descriptorSetLayout);
    _depthBuffer->recreate(SwapChainHandler::getInstance()->getSwapChainExtent());
    _framebuffers->setupFramebuffers(_shader->getRenderPass(), _depthBuffer);

    for (Entity* e : _children) {
        e->vertex()->recreate();
        e->index()->recreate();
        e->uniform()->recreate();
        e->recreate();
    }

    this->renderEntitys();
}

void Renderer::cleanup() {
    vkFreeCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), DeviceHandler::getInstance()->getCommandPool(), static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());
}

void Renderer::setFramebufferResized() {
    this->_framebufferResized = true;
}

void Renderer::setupSyncObjects() {
    this->_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    this->_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    this->_imagesInFlight.resize(SwapChainHandler::getInstance()->getSwapChainImages().size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(DeviceHandler::getInstance()->getLogicalDevice(), &semaphoreInfo, nullptr, &this->_imageAvailableSemaphores[i]) != VK_SUCCESS || vkCreateSemaphore(DeviceHandler::getInstance()->getLogicalDevice(), &semaphoreInfo, nullptr, &this->_renderFinishedSemaphores[i]) != VK_SUCCESS || vkCreateFence(DeviceHandler::getInstance()->getLogicalDevice(), &fenceInfo, nullptr, &this->_inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
        else {
            std::cout << "\t- created synchronization object for a frame!" << std::endl;
        }
    }
}

Renderer::~Renderer() {
    for (Entity* e : _children) {
        delete e;
    }
    _children.clear();

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(DeviceHandler::getInstance()->getLogicalDevice(), this->_renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(DeviceHandler::getInstance()->getLogicalDevice(), this->_imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(DeviceHandler::getInstance()->getLogicalDevice(), this->_inFlightFences[i], nullptr);
    }

    vkFreeCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), DeviceHandler::getInstance()->getCommandPool(), static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());

    delete _depthBuffer;
    delete _framebuffers;
    delete _shader;
}

