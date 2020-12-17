
#ifndef TEXTUREBUFFER_CLASS
#define TEXTUREBUFFER_CLASS

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "buffer.h"

#include <iostream>
#include <vector>
#include <string>

class TextureBuffer : Buffer {
public:
	TextureBuffer(VkInstance _instance, DeviceHandler* _deviceHandler, VkQueue _graphicsQueue, VkCommandPool _commandPool);
	~TextureBuffer();

	void loadTexture(const char* _path);

private:
	VkImage _textureImage;
	VkDeviceMemory _textureImageMemory;

	void createTextureImage(const char* _path);
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
};
#endif