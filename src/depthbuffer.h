/// @file depthbuffer.h
/// @brief Standalone header providing Buffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef DEPTHBUFFER_CLASS
#define DEPTHBUFFER_CLASS

#define GLM_DEPTH_ZERO_TO_ONE

#include "imagebuffer.h"
#include "swapchainhandler.h"

#include <iostream>
#include <vector>
#include <string>

namespace pad {

/// @brief Class describing a DepthBuffer object, which stores depth buffer image data.
///
/// The DepthBuffer class is an extension of the ImageBuffer. 
/// The class uses the functionality from both the Buffer and ImageBuffer classes to create and store a depth buffer image. 
/// By using the functions within the ImageBuffer the TextureBuffer easily creates the needed type of image. 
/// A depth buffer image is a grayscale render of the Scene on which the depth can clearly be seen. This image is then used to determine in which order of rendering for all objects.

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

}

#endif