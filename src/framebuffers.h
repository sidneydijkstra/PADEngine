/// @file framebuffers.h
/// @brief Standalone header providing Buffer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef FRAMEBUFFERS_CLASS
#define FRAMEBUFFERS_CLASS

#include "swapchainhandler.h"
#include "depthbuffer.h"
#include "samplingbuffer.h"

/// @brief Class describing FrameBuffers object, which stores buffers for multiple VkFramebuffer objects.
class FrameBuffers {
	public:
		/// @brief The constructor for the FrameBuffers class.
		FrameBuffers();
		/// @brief The deconstructor for the FrameBuffers class.
		~FrameBuffers();

		/// @brief Setup frame buffer based on correct buffer objects.
		/// @param _renderPass VkRenderPass to use.
		/// @param _depthBuffer DepthBuffer object to use.
		/// @param _samplingBuffer SamplingBuffer object to use.
		void setupFramebuffers(VkRenderPass _renderPass, DepthBuffer* _depthBuffer, SamplingBuffer* _samplingBuffer);

		/// @brief Get VkFramebuffer objects.
		/// @return A std::vector of VkFramebuffer objects.
		std::vector<VkFramebuffer> getFrameBuffers();
		int getFrameBuffersSize();
	private:

		std::vector<VkFramebuffer> _framebuffers; ///< @brief std::vector of VkFramebuffer objects.
};
#endif