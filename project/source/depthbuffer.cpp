#include "depthbuffer.h"

DepthBuffer::DepthBuffer() : ImageBuffer(){
    setupDepthResources();
}

VkImageView DepthBuffer::getImageView() {
    return this->_depthImageView;
}

void DepthBuffer::setupDepthResources() {
    VkFormat depthFormat = DeviceHandler::getInstance()->findDepthFormat();

    createImage(SwapChainHandler::getInstance()->getSwapChainExtent().width, SwapChainHandler::getInstance()->getSwapChainExtent().height, DeviceHandler::getInstance()->getMsaaSamples(), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _depthImage, _depthImageMemory);
    _depthImageView = createImageView(_depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
    transitionImageLayout(_depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void DepthBuffer::recreate() {
    vkDestroyImageView(DeviceHandler::getInstance()->getLogicalDevice(), _depthImageView, nullptr);
    vkDestroyImage(DeviceHandler::getInstance()->getLogicalDevice(), _depthImage, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _depthImageMemory, nullptr);

    setupDepthResources();
}

DepthBuffer::~DepthBuffer() {
    vkDestroyImageView(DeviceHandler::getInstance()->getLogicalDevice(), _depthImageView, nullptr);
    vkDestroyImage(DeviceHandler::getInstance()->getLogicalDevice(), _depthImage, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _depthImageMemory, nullptr);
}