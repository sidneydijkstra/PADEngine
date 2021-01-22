
#ifndef DEPTHBUFFER_CLASS
#define DEPTHBUFFER_CLASS

#include "imagebuffer.h"
#include "swapchainhandler.h"

#include <iostream>
#include <vector>
#include <string>

struct DepthBufferData {
	VkImageView depthImageView;
};

class DepthBuffer : ImageBuffer {
public:
	DepthBuffer();
	~DepthBuffer();

	void setupBuffer();
	DepthBufferData getBuffer();
	void recreate(VkExtent2D _swapChainExtent);

private:
	VkImage _depthImage;
	VkDeviceMemory _depthImageMemory;
	VkImageView _depthImageView;

	void setupDepthResources(VkExtent2D _swapChainExtent);
};
#endif