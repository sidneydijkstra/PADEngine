#include "framebuffers.h"

namespace pad {

FrameBuffers::FrameBuffers() {
}

void FrameBuffers::setupFramebuffers(VkRenderPass _renderPass, DepthBuffer* _depthBuffer, SamplingBuffer* _samplingBuffer) {
    if (!this->_framebuffers.empty()) {
        for (size_t i = 0; i < _framebuffers.size(); i++) {
            vkDestroyFramebuffer(DeviceHandler::getInstance()->getLogicalDevice(), _framebuffers[i], nullptr);
        }
        _framebuffers.clear();
    }

    int size = SwapChainHandler::getInstance()->getSwapChainImagesSize();
    this->_framebuffers.resize(size);

    for (size_t i = 0; i < size; i++) {
        std::array<VkImageView, 3> attachments = {
            _samplingBuffer->getImageView(),
            _depthBuffer->getImageView(),
            SwapChainHandler::getInstance()->getSwapChainImageViews()[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = _renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = SwapChainHandler::getInstance()->getSwapChainWidth();
        framebufferInfo.height = SwapChainHandler::getInstance()->getSwapChainHeight();
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(DeviceHandler::getInstance()->getLogicalDevice(), &framebufferInfo, nullptr, &this->_framebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
        else {
            std::cout << "\t- created framebuffer!" << std::endl;
        }
    }
}

std::vector<VkFramebuffer> FrameBuffers::getFrameBuffers() {
    return this->_framebuffers;
}

int FrameBuffers::getFrameBuffersSize() {
    return this->_framebuffers.size();
}

FrameBuffers::~FrameBuffers() {
    for (size_t i = 0; i < _framebuffers.size(); i++) {
        vkDestroyFramebuffer(DeviceHandler::getInstance()->getLogicalDevice(), _framebuffers[i], nullptr);
    }
}

}