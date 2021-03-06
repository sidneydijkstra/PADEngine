/// @file renderer.h
/// @brief Standalone header providing Renderer functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef RENDERER_CLASS
#define RENDERER_CLASS

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

#include <cstdint>
#include <chrono>

#include <iostream>
#include <array>
#include <vector>

namespace pad {

/// @brief Class describing a Renderer object, which handles all rendering tasks.
///
/// The Renderer class has the same structure as most OpenGL engines their renderers, containing separate functions to render different objects. 
/// A big difference between the OpenGL standard of a Renderer and this Vulkan implementation is that here for all operations it needs to be clear which frame is currently rendering, this information is fetched from the SequenceManager. 

class Renderer {
	public:
		/// @brief The constructor for the Renderer class.
		Renderer();
		/// @brief The deconstructor for the Renderer class.
		~Renderer();

		/// @brief Function to render a Scene.
		/// @param _scene Pointer to Scene that needs to be renderd.
		/// @param _index Current index of SequenceManager.
		/// @return VkCommandBuffer in use.
		VkCommandBuffer renderScene(Scene* _scene, int _index);

		/// @brief Function to recreate the renderer.
		void recreate();

	private:
		RenderPass* _renderPass; ///< @brief RenderPass object pointer of Renderer.
		DepthBuffer* _depthBuffer; ///< @brief DepthBuffer object pointer of Renderer.
		SamplingBuffer* _samplingBuffer; ///< @brief SamplingBuffer object pointer of Renderer.
		FrameBuffers* _framebuffers; ///< @brief FrameBuffers object pointer of Renderer.
		std::vector<VkCommandBuffer> _commandBuffers; ///< @brief A std::vector of VkCommandBuffer.

		/// @brief Function to render a Entity.
		/// @param _index Current index of SequenceManager.
		/// @param _scene Pointer to Scene that needs to be used while rendering.
		/// @param _entity Pointer to Entity that needs to be renderd.
		/// @param _material Pointer to Material that needs to be used while rendering.
		void renderEntity(int _index, Scene* _scene, Entity* _entity, MaterialBuffer* _material);

		/// @brief Function to render Entity in bulk, this means entities with the same mesh shape (vertisie/indecie buffers can be bound once for all objects).
		/// @param _index Current index of SequenceManager.
		/// @param _scene Pointer to Scene that needs to be used while rendering.
		/// @param _entities List of Entity pointers that need to be renderd.
		/// @param _material Pointer to Material that needs to be used while rendering.
		void renderEntityBulk(int _index, Scene* _scene, std::vector<Entity*> _entities, MaterialBuffer* _material);

		/// @brief Begin a command buffer.
		/// @param _index Current index of SequenceManager.
		void beginCommandBuffer(int _index);

		/// @brief End a command buffer.
		/// @param _index Current index of SequenceManager.
		void endCommandBuffer(int _index);

		/// @brief Function to setup VkRenderPassBeginInfo.
		/// @param _clearColors The colors to clear the screen with.
		/// @param _material The MaterialBuffer with the renderpass to use.
		/// @param _framebuffer VkFramebuffer to render on.
		VkRenderPassBeginInfo setupRenderPassInfo(std::vector<VkClearValue>& _clearColors, MaterialBuffer* _material, VkFramebuffer _framebuffer);

		/// @brief Setup command buffers.
		void setupCommandBuffers();

		/// @brief Update command buffers.
		/// @param _scene Pointer to Scene that needs to be renderd.
		/// @param _index Current index of SequenceManager.
		/// @return VkCommandBuffer in use.
		VkCommandBuffer updateCommandBuffers(Scene* _scene, int _index);
};

}

#endif