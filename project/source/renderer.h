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

#include "devicehandler.h"
#include "swapchainhandler.h"
#include "vulkanhandler.h"
#include "framebuffers.h"
#include "shader.h"
#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "uniformbuffer.h"
#include "texturebuffer.h"
#include "depthbuffer.h"
#include "entity.h"

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

	void draw();
	void setFramebufferResized();
private:
	Shader* _shader;

	std::vector<Entity*> _children;
	DepthBuffer* _depthBuffer;

	FrameBuffers* _framebuffers;

	std::vector<VkCommandBuffer> _commandBuffers;

	std::vector<VkSemaphore> _imageAvailableSemaphores;
	std::vector<VkSemaphore> _renderFinishedSemaphores;
	std::vector<VkFence> _inFlightFences;
	std::vector<VkFence> _imagesInFlight;
	size_t _currentFrame = 0;
	bool _framebufferResized = false;

	void recreate();
	void cleanup();

	void update(int _index);
	void renderEntitys(int _index);

	void beginCommandBuffer(int _index);
	void endCommandBuffer(int _index);

	void setupCommandBuffers();
	void updateCommandBuffers(int _index);
	void setupSyncObjects();

	const int MAX_FRAMES_IN_FLIGHT = 2;
};
#endif