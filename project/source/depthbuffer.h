
#ifndef DEPTHBUFFER_CLASS
#define DEPTHBUFFER_CLASS

#include "imagebuffer.h"
#include "swapchainhandler.h"

#include <iostream>
#include <vector>
#include <string>

class DepthBuffer : ImageBuffer {
public:
	DepthBuffer();
	~DepthBuffer();

	VkImageView getImageView();
	void recreate();

private:
	VkImage _depthImage;
	VkDeviceMemory _depthImageMemory;
	VkImageView _depthImageView;

	void setupDepthResources();
};
#endif