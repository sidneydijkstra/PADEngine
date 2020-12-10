#include "renderer.h"

Renderer::Renderer(VkInstance _instance, DeviceHandler* _deviceHandler, SwapChainHandler* _swapChainHandler) {
	this->_instance = _instance;
	this->_deviceHandler = _deviceHandler;
	this->_swapChainHandler = _swapChainHandler;

    this->_shader = new Shader(this->_instance, this->_deviceHandler, this->_swapChainHandler, "shaders/vert.spv", "shaders/frag.spv");

    this->_swapChainHandler->setupFramebuffers(_shader->getRenderPass());

    this->_deviceHandler->getDevicePresentQueue(_presentQueue);
    this->_deviceHandler->getDeviceGraphicsQueue(_graphicsQueue);

    this->setupCommandPool();
    this->setupVertexBuffer();
    this->setupCommandBuffers();
    this->setupSyncObjects();


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

        VkBuffer vertexBuffers[] = { this->_vertexBuffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(this->_commandBuffers[i], 0, 1, vertexBuffers, offsets);
        

        std::cout << "vertices-size" << std::to_string(vertices.size()) << std::endl;
        vkCmdDraw(this->_commandBuffers[i], static_cast<uint32_t>(vertices.size()), 1, 0, 0);
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

void Renderer::setupBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) { // TODO: new
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(this->_deviceHandler->getLogicalDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(this->_deviceHandler->getLogicalDevice(), buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(this->_deviceHandler->getLogicalDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(this->_deviceHandler->getLogicalDevice(), buffer, bufferMemory, 0);
}

void Renderer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = _commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(this->_deviceHandler->getLogicalDevice(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0; // Optional
    copyRegion.dstOffset = 0; // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(_graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(_graphicsQueue);

    vkFreeCommandBuffers(this->_deviceHandler->getLogicalDevice(), _commandPool, 1, &commandBuffer);
}

void Renderer::setupVertexBuffer() { // TODO: new
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    this->setupBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory);

    this->setupBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _vertexBuffer, _vertexBufferMemory);
    this->copyBuffer(stagingBuffer, _vertexBuffer, bufferSize);

    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), stagingBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), stagingBufferMemory, nullptr);
}

uint32_t Renderer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) { // TODO: new
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(this->_deviceHandler->getPhysicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void Renderer::draw() {
    vkWaitForFences(this->_deviceHandler->getLogicalDevice(), 1, &this->_inFlightFences[this->_currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(this->_deviceHandler->getLogicalDevice(), this->_swapChainHandler->getSwapChain(), UINT64_MAX, this->_imageAvailableSemaphores[this->_currentFrame], VK_NULL_HANDLE, &imageIndex);

    // Check if a previous frame is using this image (i.e. there is its fence to wait on)
    if (imageIndex == UINT64_MAX || this->_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(this->_deviceHandler->getLogicalDevice(), 1, &this->_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
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

    this->_currentFrame = (this->_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

    vkQueuePresentKHR(this->_presentQueue, &presentInfo);
    vkQueueWaitIdle(this->_presentQueue);
}

Renderer::~Renderer() {
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(this->_deviceHandler->getLogicalDevice(), this->_renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(this->_deviceHandler->getLogicalDevice(), this->_imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(this->_deviceHandler->getLogicalDevice(), this->_inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(this->_deviceHandler->getLogicalDevice(), this->_commandPool, nullptr);

    vkDestroyBuffer(this->_deviceHandler->getLogicalDevice(), _vertexBuffer, nullptr);
    vkFreeMemory(this->_deviceHandler->getLogicalDevice(), _vertexBufferMemory, nullptr);

    delete _shader;
}

