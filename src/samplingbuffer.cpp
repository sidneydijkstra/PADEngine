#include "samplingbuffer.h"

SamplingBuffer::SamplingBuffer() : ImageBuffer() {
    this->setupResources();
}

VkImageView SamplingBuffer::getImageView() {
    return this->_colorImageView;
}

void SamplingBuffer::recreate() {
    vkDestroyImageView(DeviceHandler::getInstance()->getLogicalDevice(), _colorImageView, nullptr);
    vkDestroyImage(DeviceHandler::getInstance()->getLogicalDevice(), _colorImage, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _colorImageMemory, nullptr);

    this->setupResources();
}

void SamplingBuffer::setupResources() {
    VkFormat colorFormat = SwapChainHandler::getInstance()->getSwapChainImageFormat();

    createImage(SwapChainHandler::getInstance()->getSwapChainWidth(), SwapChainHandler::getInstance()->getSwapChainHeight(), DeviceHandler::getInstance()->getMsaaSamples(), colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _colorImage, _colorImageMemory);
    _colorImageView = createImageView(_colorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT);
}

SamplingBuffer::~SamplingBuffer() {
    vkDestroyImageView(DeviceHandler::getInstance()->getLogicalDevice(), _colorImageView, nullptr);
    vkDestroyImage(DeviceHandler::getInstance()->getLogicalDevice(), _colorImage, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _colorImageMemory, nullptr);
}
