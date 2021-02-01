

#ifndef IMAGEBUFFER_CLASS
#define IMAGEBUFFER_CLASS

#include "buffer.h"

class ImageBuffer : public Buffer {
	public:
		ImageBuffer();
		~ImageBuffer();

	protected:
		void createImage(uint32_t _width, uint32_t _height, VkSampleCountFlagBits _numSamples, VkFormat _format, VkImageTiling _tiling, VkImageUsageFlags _usage, VkMemoryPropertyFlags _properties, VkImage& _image, VkDeviceMemory& _imageMemory);
		void transitionImageLayout(VkImage _image, VkFormat _format, VkImageLayout _oldLayout, VkImageLayout _newLayout);
		void copyBufferToImage(VkBuffer _buffer, VkImage _image, uint32_t _width, uint32_t _height);
		VkImageView createImageView(VkImage _image, VkFormat _format, VkImageAspectFlagBits _flag);
};
#endif