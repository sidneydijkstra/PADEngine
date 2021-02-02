/// @file depthbuffer.h
/// @brief Standalone header providing Buffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef DEPTHBUFFER_CLASS
#define DEPTHBUFFER_CLASS

#include "imagebuffer.h"
#include "swapchainhandler.h"

#include <iostream>
#include <vector>
#include <string>

/// @brief Class describing a DepthBuffer object, which stores depth buffer image data.
class DepthBuffer : ImageBuffer {
public:
	/// @brief The constructor for the DepthBuffer class.
	DepthBuffer();
	/// @brief The deconstructor for the DepthBuffer class.
	~DepthBuffer();

	/// @brief Return the image view of the DepthBuffer.
	/// @return A VkImageView object containing a depth buffer image.
	VkImageView getImageView();
	void recreate();

private:
	VkImage _depthImage; ///< @brief VkImage object containing image.
	VkDeviceMemory _depthImageMemory; ///< @brief VkDeviceMemory object containing device memory for image.
	VkImageView _depthImageView; ///< @brief VkImageView object containing image view.

	/// @brief Setup the depth buffer resource.
	void setupDepthResources();
};
#endif