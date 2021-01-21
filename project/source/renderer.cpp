#include "renderer.h"

Renderer::Renderer() {
    this->_renderPass = new RenderPass();
    this->_shaderEffect = new ShaderEffect("shaders/vert.spv", "shaders/frag.spv");
    this->_shaderPass = new ShaderPass(_renderPass->getRenderPass(), _shaderEffect);

    MaterialManager::getInstance()->load("mat_normal_PBR", _shaderPass);

    _depthBuffer = new DepthBuffer();

    _framebuffers = new FrameBuffers();
    _framebuffers->setupFramebuffers(_renderPass->getRenderPass(), _depthBuffer);

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
    renderPassInfo.renderPass = _renderPass->getRenderPass();
    renderPassInfo.framebuffer = _framebuffers->getFrameBuffers()[_index];

    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = SwapChainHandler::getInstance()->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
    clearValues[1].depthStencil = { 1.0f, 0 };

    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(this->_commandBuffers[_index], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(this->_commandBuffers[_index], VK_PIPELINE_BIND_POINT_GRAPHICS, this->_shaderPass->getPipeline());

    // get children sorted by mesh type
    std::map<MeshType, std::vector<Entity*>> children = RenderFactory::sortEntitiesByMeshType(_scene->getChildren());

    // iterate all the diffrent meshes
    std::map<MeshType, std::vector<Entity*>>::iterator children_it;
    for (children_it = children.begin(); children_it != children.end(); ++children_it) {

        // get children vector
        std::vector<Entity*> childVector = children_it->second;

        // get and bind vertex/index buffer
        BufferData vertexData = childVector[0]->mesh()->getBuffer()->vertex()->getBuffer();
        BufferData indexData = childVector[0]->mesh()->getBuffer()->index()->getBuffer();

        VkBuffer vertexBuffers[] = { vertexData.buffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(this->_commandBuffers[_index], 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(this->_commandBuffers[_index], indexData.buffer, 0, VK_INDEX_TYPE_UINT16);

        for (Entity* entity : childVector) {
            // set descriptor and draw mesh
            vkCmdBindDescriptorSets(_commandBuffers[_index], VK_PIPELINE_BIND_POINT_GRAPHICS, _shaderPass->getPipelineLayout(), 0, 1, &entity->description()[_index], 0, nullptr);
            vkCmdDrawIndexed(_commandBuffers[_index], static_cast<uint32_t>(indexData.size), 1, 0, 0, 0);
        }

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

    _shaderPass->recreate();

    _depthBuffer->recreate(SwapChainHandler::getInstance()->getSwapChainExtent());
    _framebuffers->setupFramebuffers(_renderPass->getRenderPass(), _depthBuffer);

    vkFreeCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), DeviceHandler::getInstance()->getCommandPool(), static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());
    setupCommandBuffers();
}



Renderer::~Renderer() {
    vkFreeCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), DeviceHandler::getInstance()->getCommandPool(), static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());

    ShaderManager::deleteInsance();

    delete _depthBuffer;
    delete _framebuffers;
    delete _renderPass;
    delete _shaderPass;
    delete _shaderEffect;
}

