
#ifndef SAMPLINGBUFFER_CLASS
#define SAMPLINGBUFFER_CLASS

#include "swapchainhandler.h"
#include "imagebuffer.h"

class SamplingBuffer : ImageBuffer {
	public:
		SamplingBuffer();
		~SamplingBuffer();

		VkImageView getImageView();
		void recreate();

	private:
		VkImage _colorImage;
		VkDeviceMemory _colorImageMemory;
		VkImageView _colorImageView;

		void setupColorResources();
};
#endif