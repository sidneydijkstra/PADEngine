#include <cstdint>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "materialmanager.h"
#include "renderfactory.h"
#include "devicehandler.h"
#include "swapchainhandler.h"
#include "vulkanhandler.h"
#include "framebuffers.h"
#include "shadereffect.h"
#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "uniformbuffer.h"
#include "texturebuffer.h"
#include "depthbuffer.h"
#include "samplingbuffer.h"
#include "entity.h"
#include "scene.h"

#include "renderpass.h"
#include "shaderpass.h"

#include <chrono>

#include <iostream>
#include <array>
#include <vector>

#ifndef RENDERER_CLASS
#define RENDERER_CLASS

class Renderer {
	public:
		Renderer();
		~Renderer();

		void recreate();
		VkCommandBuffer renderScene(Scene* _scene, int _index);

	private:
		RenderPass* _renderPass;

		DepthBuffer* _depthBuffer;
		SamplingBuffer* _samplingBuffer;
		FrameBuffers* _framebuffers;

		std::vector<VkCommandBuffer> _commandBuffers;

		void beginCommandBuffer(int _index);
		void endCommandBuffer(int _index);

		void setupCommandBuffers();
		VkCommandBuffer updateCommandBuffers(Scene* _scene, int _index);
};
#endif