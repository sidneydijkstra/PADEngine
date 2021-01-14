#include "renderer.h"

Renderer::Renderer() {
    this->_shader = new Shader("shaders/vert.spv", "shaders/frag.spv", ResourceManager::getInstance()->getEntityDescriptor()->getLayout());

    _depthBuffer = new DepthBuffer();

    _framebuffers = new FrameBuffers();
    _framebuffers->setupFramebuffers(_shader->getRenderPass(), _depthBuffer);

    setupCommandBuffers();
}

VkCommandBuffer Renderer::renderScene(Scene* _scene, int _index) {
    return this->updateCommandBuffers(_scene, _index);
}

void Renderer::beginCommandBuffer(int _index) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0; // Optional
    beginInfo.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(this->_commandBuffers[_index], &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
}

void Renderer::endCommandBuffer(int _index) {
    if (vkEndCommandBuffer(this->_commandBuffers[_index]) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void Renderer::setupCommandBuffers() {
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
        //this->updateCommandBuffers(i);
    }
}

VkCommandBuffer Renderer::updateCommandBuffers(Scene* _scene, int _index) {
    beginCommandBuffer(_index);

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = this->_shader->getRenderPass();
    renderPassInfo.framebuffer = _framebuffers->getFrameBuffers()[_index];

    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = SwapChainHandler::getInstance()->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
    clearValues[1].depthStencil = { 1.0f, 0 };

    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(this->_commandBuffers[_index], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(this->_commandBuffers[_index], VK_PIPELINE_BIND_POINT_GRAPHICS, this->_shader->getGraphicsPipeline());

    for (Entity* ent : _scene->getChildren()) {
        BufferData vertexData = ent->vertex()->getBuffer();
        BufferData indexData = ent->index()->getBuffer();

        VkBuffer vertexBuffers[] = { vertexData.buffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(this->_commandBuffers[_index], 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(this->_commandBuffers[_index], indexData.buffer, 0, VK_INDEX_TYPE_UINT16);

        vkCmdBindDescriptorSets(_commandBuffers[_index], VK_PIPELINE_BIND_POINT_GRAPHICS, _shader->getPipelineLayout(), 0, 1, &ent->description()[_index], 0, nullptr);
        vkCmdDrawIndexed(_commandBuffers[_index], static_cast<uint32_t>(indexData.size), 1, 0, 0, 0);
    }

    vkCmdEndRenderPass(this->_commandBuffers[_index]);

    endCommandBuffer(_index);

    return this->_commandBuffers[_index];
}

void Renderer::recreate() {
    int width = 0, height = 0;
    glfwGetFramebufferSize(VulkanHandler::getInstance()->getWindow(), &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(VulkanHandler::getInstance()->getWindow(), &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(DeviceHandler::getInstance()->getLogicalDevice());

    SwapChainHandler::getInstance()->recreate();

    delete _shader;
    this->_shader = new Shader("shaders/vert.spv", "shaders/frag.spv", ResourceManager::getInstance()->getEntityDescriptor()->getLayout());

    _depthBuffer->recreate(SwapChainHandler::getInstance()->getSwapChainExtent());
    _framebuffers->setupFramebuffers(_shader->getRenderPass(), _depthBuffer);

    vkFreeCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), DeviceHandler::getInstance()->getCommandPool(), static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());
    setupCommandBuffers();
}



Renderer::~Renderer() {
    vkFreeCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), DeviceHandler::getInstance()->getCommandPool(), static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());

    delete _depthBuffer;
    delete _framebuffers;
    delete _shader;
}

