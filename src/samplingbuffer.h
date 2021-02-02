/// @file samplingbuffer.h
/// @brief Standalone header providing SamplingBuffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef SAMPLINGBUFFER_CLASS
#define SAMPLINGBUFFER_CLASS

#include "swapchainhandler.h"
#include "imagebuffer.h"

/// @brief Class describing a SamplingBuffer object, which stores all the information msaa image sampling.
class SamplingBuffer : ImageBuffer {
	public:
		/// @brief The constructor for the SamplingBuffer class.
		SamplingBuffer();
		/// @brief The deconstructor for the SamplingBuffer class.
		~SamplingBuffer();

		/// @brief Get the VkImageView of buffer.
		/// @return The VkImageView.
		VkImageView getImageView();

		/// @brief Recreate the SamplingBuffer.
		void recreate();

	private:
		VkImage _colorImage; ///< @brief VkImage object of SamplingBuffer.
		VkDeviceMemory _colorImageMemory; ///< @brief VkDeviceMemory object of SamplingBuffer.
		VkImageView _colorImageView; ///< @brief VkImageView object of SamplingBuffer.

		/// @brief Setup msaa sample resource.
		void setupResources();
};
#endif