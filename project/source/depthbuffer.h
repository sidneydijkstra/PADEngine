
#ifndef DEPTHBUFFER_CLASS
#define DEPTHBUFFER_CLASS

#include "buffer.h"

#include <iostream>
#include <vector>
#include <string>

struct DepthBufferData {
	VkImageView depthImageView;
};

class DepthBuffer : Buffer {
public:
	DepthBuffer(VkInstance _instance, DeviceHandler* _deviceHandler, VkQueue _graphicsQueue, VkCommandPool _commandPool);
	~DepthBuffer();

	void setupBuffer(VkExtent2D _swapChainExtent);
	DepthBufferData getBuffer();
	void recreate(VkExtent2D _swapChainExtent);

private:
	VkImage _depthImage;
	VkDeviceMemory _depthImageMemory;
	VkImageView _depthImageView;

	void setupDepthResources(VkExtent2D _swapChainExtent);

	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	VkImageView createImageView(VkImage image, VkFormat format);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
};
#endif