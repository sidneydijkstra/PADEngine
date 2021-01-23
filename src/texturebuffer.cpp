#include "texturebuffer.h"


TextureBuffer::TextureBuffer(const char* _path) : ImageBuffer() {
    this->createTextureImage(_path);
    createTextureImageView();
    createTextureSampler();
}

VkImage TextureBuffer::getImage() {
    return _textureImage;
}

VkDeviceMemory TextureBuffer::getImageMemory() {
    return _textureImageMemory;
}

VkImageView TextureBuffer::getImageView() {
    return _textureImageView;
}

VkSampler TextureBuffer::getSampler() {
    return _textureSampler;
}

void TextureBuffer::createTextureImage(const char* _path) {
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load(_path, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;

    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vkUnmapMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory);
    stbi_image_free(pixels);

    createImage(texWidth, texHeight, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _textureImage, _textureImageMemory);
    transitionImageLayout(_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(stagingBuffer, _textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    transitionImageLayout(_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vkDestroyBuffer(DeviceHandler::getInstance()->getLogicalDevice(), stagingBuffer, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), stagingBufferMemory, nullptr);
}

void TextureBuffer::createTextureImageView() {
    _textureImageView = createImageView(_textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
}

void TextureBuffer::createTextureSampler() {
    VkPhysicalDeviceProperties properties{};
    vkGetPhysicalDeviceProperties(DeviceHandler::getInstance()->getPhysicalDevice(), &properties);

    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;
    samplerInfo.anisotropyEnable = VK_FALSE;
    samplerInfo.maxAnisotropy = 1.0f;

    if (vkCreateSampler(DeviceHandler::getInstance()->getLogicalDevice(), &samplerInfo, nullptr, &_textureSampler) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture sampler!");
    }
}

TextureBuffer::~TextureBuffer() {
    vkDestroySampler(DeviceHandler::getInstance()->getLogicalDevice(), _textureSampler, nullptr);
    vkDestroyImageView(DeviceHandler::getInstance()->getLogicalDevice(), _textureImageView, nullptr);
    vkDestroyImage(DeviceHandler::getInstance()->getLogicalDevice(), _textureImage, nullptr);
    vkFreeMemory(DeviceHandler::getInstance()->getLogicalDevice(), _textureImageMemory, nullptr);
}
