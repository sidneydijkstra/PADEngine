
#ifndef TEXTUREBUFFER_CLASS
#define TEXTUREBUFFER_CLASS

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "buffer.h"

#include <iostream>
#include <vector>
#include <string>
#include <array>

struct TextureBufferData {
	VkImageView textureImageView;
	VkSampler textureSampler;
};

class TextureBuffer : Buffer {
public:
	TextureBuffer(VkInstance _instance, VkCommandPool _commandPool);
	~TextureBuffer();

	void loadTexture(const char* _path);
	void textureToSwapChain(const char* _path, std::vector<VkImageView>& _swapChainImageViews, std::vector<VkImage> _swapChainImages, VkFormat _format);
	TextureBufferData getBuffer();


private:
	VkImage _textureImage;
	VkDeviceMemory _textureImageMemory;

	VkImageView _textureImageView;

	VkSampler _textureSampler;

	// image loading
	void createTextureImage(const char* _path);
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	// image view and sampler
	void createTextureImageView();
	VkImageView createImageView(VkImage image, VkFormat format);
	void createTextureSampler();
};
#endif