
#ifndef FRAMEBUFFERS_CLASS
#define FRAMEBUFFERS_CLASS

#include "swapchainhandler.h"
#include "depthbuffer.h"
#include "samplingbuffer.h"

class FrameBuffers {
	public:
		FrameBuffers();
		~FrameBuffers();

		void setupFramebuffers(VkRenderPass _renderPass, DepthBuffer* _depthBuffer, SamplingBuffer* _samplingBuffer);
		std::vector<VkFramebuffer> getFrameBuffers();
		int getFrameBuffersSize();
	private:

		std::vector<VkFramebuffer> _framebuffers;
};
#endif