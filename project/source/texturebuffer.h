
#ifndef TEXTUREBUFFER_CLASS
#define TEXTUREBUFFER_CLASS

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "imagebuffer.h"

#include <iostream>
#include <vector>
#include <string>
#include <array>

struct TextureBufferData {
	VkImageView textureImageView;
	VkSampler textureSampler;
};

class TextureBuffer : ImageBuffer {
public:
	TextureBuffer(const char* _path);
	~TextureBuffer();

	//void textureToSwapChain(const char* _path, std::vector<VkImageView>& _swapChainImageViews, std::vector<VkImage> _swapChainImages, VkFormat _format);

	VkImage getImage();
	VkDeviceMemory getImageMemory();
	VkImageView getImageView();
	VkSampler getSampler();

private:
	VkImage _textureImage;
	VkDeviceMemory _textureImageMemory;
	VkImageView _textureImageView;
	VkSampler _textureSampler;

	// image loading
	void createTextureImage(const char* _path);

	// image view and sampler
	void createTextureImageView();
	void createTextureSampler();
};
#endif