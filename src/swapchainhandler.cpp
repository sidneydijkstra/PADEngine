#include "swapchainhandler.h"

namespace pad {

static SwapChainHandler* _instance;

SwapChainHandler::SwapChainHandler() {
}

SwapChainHandler* SwapChainHandler::getInstance() {
    if (!_instance) {
        _instance = new SwapChainHandler();
    }
    return _instance;
}

void SwapChainHandler::init() {
    //if(!_swapChain)
        this->setupSwapChain();
}

void SwapChainHandler::deleteInstance() {
    delete _instance;
    _instance = nullptr;
}

void SwapChainHandler::recreate() {
    this->cleanup();
    this->createSwapChain();
    this->createImageView();
}

void SwapChainHandler::cleanup() {
    for (size_t i = 0; i < _swapChainImageViews.size(); i++) {
        vkDestroyImageView(DeviceHandler::getInstance()->getLogicalDevice(), _swapChainImageViews[i], nullptr);
    }
    vkDestroySwapchainKHR(DeviceHandler::getInstance()->getLogicalDevice(), _swapChain, nullptr);
}

void SwapChainHandler::setupSwapChain() {
    this->createSwapChain();
    this->createImageView();
}

VkSwapchainKHR SwapChainHandler::getSwapChain() {
    return this->_swapChain;
}

std::vector<VkImage> SwapChainHandler::getSwapChainImages() {
    return this->_swapChainImages;
}

std::vector<VkImageView> SwapChainHandler::getSwapChainImageViews() {
    return this->_swapChainImageViews;
}

int SwapChainHandler::getSwapChainImagesSize() {
    return this->_swapChainImages.size();
}

VkFormat SwapChainHandler::getSwapChainImageFormat() {
    return this->_swapChainImageFormat;
}

VkExtent2D SwapChainHandler::getSwapChainExtent() {
    return this->_swapChainExtent;
}

int SwapChainHandler::getSwapChainWidth() {
    return this->_swapChainExtent.width;
}

int SwapChainHandler::getSwapChainHeight() {
    return this->_swapChainExtent.height;
}

void SwapChainHandler::createSwapChain() {
    SwapChainSupportDetails swapChainSupport = DeviceHandler::getInstance()->querySwapChainSupport(DeviceHandler::getInstance()->getPhysicalDevice());

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1; // add one extra image slot in the swap-chain

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) { // check if not extend max images in swap-chain
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = VulkanHandler::getInstance()->getSurface();

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = DeviceHandler::getInstance()->findQueueFamilies(DeviceHandler::getInstance()->getPhysicalDevice());
    uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(DeviceHandler::getInstance()->getLogicalDevice(), &createInfo, nullptr, &this->_swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }
    else {
        std::cout << "created swap chain!" << std::endl;
    }

    vkGetSwapchainImagesKHR(DeviceHandler::getInstance()->getLogicalDevice(), this->_swapChain, &imageCount, nullptr);
    this->_swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(DeviceHandler::getInstance()->getLogicalDevice(), this->_swapChain, &imageCount, this->_swapChainImages.data());

    this->_swapChainImageFormat = surfaceFormat.format;
    this->_swapChainExtent = extent;
}

void SwapChainHandler::createImageView() {
    this->_swapChainImageViews.resize(this->_swapChainImages.size());

    for (size_t i = 0; i < this->_swapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = this->_swapChainImages[i];

        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = this->_swapChainImageFormat;

        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(DeviceHandler::getInstance()->getLogicalDevice(), &createInfo, nullptr, &this->_swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
        else {
            std::cout << "\t- created image view!" << std::endl;
        }
    }
}

VkSurfaceFormatKHR SwapChainHandler::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _availableFormats) {
    for (const auto& availableFormat : _availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return _availableFormats[0];
}

VkPresentModeKHR SwapChainHandler::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _availablePresentModes) {
    for (const auto& availablePresentMode : _availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChainHandler::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities) {
    if (_capabilities.currentExtent.width != UINT32_MAX) {
        return _capabilities.currentExtent;
    }
    else {
        VkExtent2D actualExtent = { Config::WIDTH, Config::HEIGHT };

        actualExtent.width = std::max(_capabilities.minImageExtent.width, std::min(_capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(_capabilities.minImageExtent.height, std::min(_capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

SwapChainHandler::~SwapChainHandler() {
    this->cleanup();
}

}
