#include "sequencemanager.h"

SequenceManager::SequenceManager() {
    this->_renderer = new Renderer();

    this->setupSyncObjects();
}

void SequenceManager::draw(Scene* _scene) {
    // wait for fence and get new index
    uint32_t imageIndex = this->getImageIndex();
    if (imageIndex == -1) {
        return;
    }

    // Mark the image as now being in use by this frame
    this->_imagesInFlight[imageIndex] = this->_inFlightFences[this->_currentFrame];

    this->updateScene(_scene, imageIndex);

    VkCommandBuffer cmdBuffer = _renderer->renderScene(_scene, imageIndex);

    this->updateSequence(cmdBuffer, imageIndex);

    this->_currentFrame = (this->_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

    vkQueueWaitIdle(DeviceHandler::getInstance()->getDevicePresentQueue());
}

Renderer* SequenceManager::getRenderer() {
    return this->_renderer;
}

void SequenceManager::updateScene(Scene* _scene, int _imageIndex) {
    // update scene
    _scene->update();

    // loop througe scene entities and update there buffers
    std::vector<Hierarchy*> allEntities = RenderFactory::getAllEntityWithChildren(_scene->getChildren());
    for (Hierarchy* hierachy : allEntities) {
        Entity* entity = (Entity*)hierachy;

        // set parent child positions
        Vector3 position = entity->position;
        Entity* parent = dynamic_cast<Entity*>(entity->getParent());
        while (parent != nullptr) {
            Entity* parentEntity = (Entity*)parent;
            position += parentEntity->position;
            parent = dynamic_cast<Entity*>(parent->getParent());
        }

        // create ubo buffor for entity
        UBOBufferObject ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.model = glm::translate(ubo.model, position.glm());
        ubo.model = glm::scale(ubo.model, entity->scale.glm());
        ubo.model = glm::rotate(ubo.model, entity->rotation.x, glm::vec3(1, 0, 0));
        ubo.model = glm::rotate(ubo.model, entity->rotation.y, glm::vec3(0, 1, 0));
        ubo.model = glm::rotate(ubo.model, entity->rotation.z, glm::vec3(0, 0, 1));


        // check camera perspective fot ortoh or perspective rendering
        if(_scene->getCamera()->getType() == PerspectiveType::PERSPECTIVE){
            ubo.view = glm::lookAt(_scene->getCamera()->position, _scene->getCamera()->position + _scene->getCamera()->front, _scene->getCamera()->up);
            ubo.proj = glm::perspective(glm::radians(_scene->getCamera()->fov), SwapChainHandler::getInstance()->getSwapChainExtent().width / (float)SwapChainHandler::getInstance()->getSwapChainExtent().height, 0.1f, 100.0f);
            ubo.proj[1][1] *= -1;
        }
        else if (_scene->getCamera()->getType() == PerspectiveType::ORTHOGRAPHIC) {
            ubo.view = glm::lookAt(_scene->getCamera()->position, _scene->getCamera()->position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
            ubo.proj = glm::ortho(0.0f, (float)Config::WIDTH, 0.0f, (float)Config::HEIGHT, 0.01f, 1000.0f);
        }

        // update ubo buffer of entity
        entity->getUniformBuffer()->updateBuffer(_imageIndex, ubo);

        // recreate entity
        entity->recreate(_imageIndex);
    }
}

void SequenceManager::recreate() {
    _renderer->recreate();
}

void SequenceManager::updateSequence(const VkCommandBuffer _commandBuffer, const uint32_t _imageIndex) {
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { this->_imageAvailableSemaphores[this->_currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &_commandBuffer;

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
    presentInfo.pImageIndices = &_imageIndex;
    presentInfo.pResults = nullptr; // Optional

    VkResult result = vkQueuePresentKHR(DeviceHandler::getInstance()->getDevicePresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _framebufferResized) {
        this->_framebufferResized = false;
        this->recreate();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }
}

uint32_t SequenceManager::getImageIndex() {
    vkWaitForFences(DeviceHandler::getInstance()->getLogicalDevice(), 1, &this->_inFlightFences[this->_currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(DeviceHandler::getInstance()->getLogicalDevice(), SwapChainHandler::getInstance()->getSwapChain(), UINT64_MAX, this->_imageAvailableSemaphores[this->_currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        this->recreate();
        return -1;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    // Check if a previous frame is using this image (i.e. there is its fence to wait on)
    if (imageIndex == UINT64_MAX || this->_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(DeviceHandler::getInstance()->getLogicalDevice(), 1, &this->_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }

    return imageIndex;
}

void SequenceManager::setupSyncObjects() {
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

void SequenceManager::setFramebufferResized() {
    this->_framebufferResized = true;
}

SequenceManager::~SequenceManager() {
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(DeviceHandler::getInstance()->getLogicalDevice(), this->_renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(DeviceHandler::getInstance()->getLogicalDevice(), this->_imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(DeviceHandler::getInstance()->getLogicalDevice(), this->_inFlightFences[i], nullptr);
    }

    delete _renderer;
}
