#include "renderer.h"

Renderer::Renderer() {
    this->_renderPass = new RenderPass();

    MaterialData mat_normal_PBR{};
    mat_normal_PBR.name = "mat_normal_PBR";
    mat_normal_PBR.vertexPath = "shaders/vert.spv";
    mat_normal_PBR.fragmentPath = "shaders/frag.spv";
    mat_normal_PBR.renderPass = _renderPass;

    MaterialData mat_normal2D_PBR{};
    mat_normal2D_PBR.name = "mat_normal2D_PBR";
    mat_normal2D_PBR.vertexPath = "shaders/vert.spv";
    mat_normal2D_PBR.fragmentPath = "shaders/frag_2D.spv";
    mat_normal2D_PBR.renderPass = _renderPass;

    MaterialManager::getInstance()->loadMaterial(mat_normal_PBR);
    MaterialManager::getInstance()->loadMaterial(mat_normal2D_PBR);

    _depthBuffer = new DepthBuffer();
    _samplingBuffer = new SamplingBuffer();

    _framebuffers = new FrameBuffers();
    _framebuffers->setupFramebuffers(_renderPass->getRenderPass(), _depthBuffer, _samplingBuffer);

    setupCommandBuffers();
}

VkCommandBuffer Renderer::renderScene(Scene* _scene, int _index) {
    return this->updateCommandBuffers(_scene, _index);
}

void Renderer::renderEntity(int _index, Scene* _scene, Entity* _entity, MaterialBuffer* _material) {
    // set vertex and index buffer
    VkBuffer vertexBuffers[] = { _entity->getMesh()->getBuffer()->vertex()->getBuffer() };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(this->_commandBuffers[_index], 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(this->_commandBuffers[_index], _entity->getMesh()->getBuffer()->index()->getBuffer(), 0, VK_INDEX_TYPE_UINT32);

    // update descriptors
    _entity->updateDescriptors(_index);
    _scene->updateDescriptors(_index, _entity);

    // set descriptors
    vkCmdBindDescriptorSets(_commandBuffers[_index], VK_PIPELINE_BIND_POINT_GRAPHICS, _material->getShaderPass()->getPipelineLayout(), 0, 1, &_entity->getDescriptorSet(_index), 0, nullptr);
    // draw mesh
    vkCmdDrawIndexed(_commandBuffers[_index], static_cast<uint32_t>(_entity->getMesh()->getBuffer()->index()->getBufferSize()), 1, 0, 0, 0);
}

void Renderer::renderEntityBulk(int _index, Scene* _scene, std::vector<Entity*> _entities, MaterialBuffer* _material) {// get and bind vertex/index buffer
    // set vertex and index buffer
    VkBuffer vertexBuffers[] = { _entities[0]->getMesh()->getBuffer()->vertex()->getBuffer() };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(this->_commandBuffers[_index], 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(this->_commandBuffers[_index], _entities[0]->getMesh()->getBuffer()->index()->getBuffer(), 0, VK_INDEX_TYPE_UINT32);

    // loop througe entities
    for (Entity* entity : _entities) {
        // update descriptors
        entity->updateDescriptors(_index);
        _scene->updateDescriptors(_index, entity);

        // set descriptors
        vkCmdBindDescriptorSets(_commandBuffers[_index], VK_PIPELINE_BIND_POINT_GRAPHICS, _material->getShaderPass()->getPipelineLayout(), 0, 1, &entity->getDescriptorSet(_index), 0, nullptr);

        // draw mesh
        vkCmdDrawIndexed(_commandBuffers[_index], static_cast<uint32_t>(entity->getMesh()->getBuffer()->index()->getBufferSize()), 1, 0, 0, 0);
    }
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

VkRenderPassBeginInfo& Renderer::setupRenderPassInfo(std::vector<VkClearValue>& _clearColors, MaterialBuffer* _material, VkFramebuffer _framebuffer) {
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = _material == nullptr ? _renderPass->getRenderPass() :_material->getShaderPass()->getRenderPass();
    renderPassInfo.framebuffer = _framebuffer;

    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = SwapChainHandler::getInstance()->getSwapChainExtent();

    renderPassInfo.clearValueCount = static_cast<uint32_t>(_clearColors.size());
    renderPassInfo.pClearValues = _clearColors.data();

    return renderPassInfo;
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
    // begin command buffer
    beginCommandBuffer(_index);

    // get all entities in scene ordering: material (name), meshtype, list of entity*
    std::map<std::string, std::map<MeshType, std::vector<Entity*>>> _ents = RenderFactory::sortEnitiesByMaterialAndMeshType(_scene->getChildren());

    std::map<std::string, std::map<MeshType, std::vector<Entity*>>>::iterator mat_children_it;
    for (mat_children_it = _ents.begin(); mat_children_it != _ents.end(); ++mat_children_it) {
        // get material of entity batch
        MaterialBuffer* mat = MaterialManager::getInstance()->getMaterial(mat_children_it->first.c_str());

        // set clear values and setup renderpassinfo
        std::vector<VkClearValue> clearValues = std::vector<VkClearValue>();
        clearValues.push_back(VkClearValue{ 0.0f, 0.0f, 0.0f, 1.0f });
        clearValues.push_back(VkClearValue{ 1.0f, 0.0f });
        VkRenderPassBeginInfo renderPassInfo = this->setupRenderPassInfo(clearValues, nullptr, _framebuffers->getFrameBuffers()[_index]);
        
        // bind renderpass
        vkCmdBeginRenderPass(this->_commandBuffers[_index], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        // bind pipeline of material
        vkCmdBindPipeline(this->_commandBuffers[_index], VK_PIPELINE_BIND_POINT_GRAPHICS, mat->getShaderPass()->getPipeline());

        // get children sorted by mesh type
        std::map<MeshType, std::vector<Entity*>> children = mat_children_it->second;

        // iterate all the diffrent meshes
        std::map<MeshType, std::vector<Entity*>>::iterator children_it;
        for (children_it = children.begin(); children_it != children.end(); ++children_it) {
            // get children vector
            std::vector<Entity*> childVector = children_it->second;

            if (children_it->first != MeshType::OBJECT) { // render mesh shape
                this->renderEntityBulk(_index, _scene, childVector, mat);
            }
            else if (children_it->first == MeshType::OBJECT) { // render object
                for (Entity* entity : childVector) {
                    this->renderEntity(_index, _scene, entity, mat);
                }
            }
        }

        // end renderpass
        vkCmdEndRenderPass(this->_commandBuffers[_index]);
    }

    // end command buffer
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

    MaterialManager::getInstance()->recreateAll();

    _depthBuffer->recreate();
    _samplingBuffer->recreate();

    _framebuffers->setupFramebuffers(_renderPass->getRenderPass(), _depthBuffer, _samplingBuffer);

    vkFreeCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), DeviceHandler::getInstance()->getCommandPool(), static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());
    setupCommandBuffers();
}



Renderer::~Renderer() {
    vkFreeCommandBuffers(DeviceHandler::getInstance()->getLogicalDevice(), DeviceHandler::getInstance()->getCommandPool(), static_cast<uint32_t>(_commandBuffers.size()), _commandBuffers.data());

    delete _depthBuffer;
    delete _samplingBuffer;
    delete _framebuffers;
    delete _renderPass;
}

