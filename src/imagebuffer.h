/// @file imagebuffer.h
/// @brief Standalone header providing ImageBuffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef IMAGEBUFFER_CLASS
#define IMAGEBUFFER_CLASS

#include "buffer.h"

/// @brief Class describing a ImageBuffer object, which stores all image data in a buffer.
class ImageBuffer : public Buffer {
	public:
		/// @brief The constructor for the ImageBuffer class.
		ImageBuffer();
		/// @brief The deconstructor for the ImageBuffer class.
		~ImageBuffer();

	protected:
		/// @brief Function to create an image.
		/// @param _width Width of image.
		/// @param _height height of image.
		/// @param _numSamples Sample count flag bit.
		/// @param _format VkFormat to use.
		/// @param _tiling VkImageTiling to use.
		/// @param _usage Image usage flag.
		/// @param _properties Memory property flags.
		/// @param _image Reference to correct VkImage.
		/// @param _imageMemory Reference to correct VkDeviceMemory.
		void createImage(uint32_t _width, uint32_t _height, VkSampleCountFlagBits _numSamples, VkFormat _format, VkImageTiling _tiling, VkImageUsageFlags _usage, VkMemoryPropertyFlags _properties, VkImage& _image, VkDeviceMemory& _imageMemory);

		/// @brief Function to transition image layout.
		/// @param _image VkImage object to use.
		/// @param _format VkFormat to use.
		/// @param _oldLayout Old VkImageLayout.
		/// @param _newLayout New VkImageLayout.
		void transitionImageLayout(VkImage _image, VkFormat _format, VkImageLayout _oldLayout, VkImageLayout _newLayout);

		/// @brief Function to copy buffer to image.
		/// @param _buffer VkBuffer object to use.
		/// @param _image VkImage object to use.
		/// @param _width Width of image.
		/// @param _height height of image.
		void copyBufferToImage(VkBuffer _buffer, VkImage _image, uint32_t _width, uint32_t _height);

		/// @brief Function to create image view.
		/// @param _image VkImage object to use.
		/// @param _format VkFormat to use.
		/// @param _flag Image aspect flag bits.
		VkImageView createImageView(VkImage _image, VkFormat _format, VkImageAspectFlagBits _flag);
};
#endif