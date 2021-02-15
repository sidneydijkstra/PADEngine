/// @file descriptor.h
/// @brief Standalone header providing Descriptor functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef DESCRIPTOR_CLASS
#define DESCRIPTOR_CLASS

#include <cstdint>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "devicehandler.h"
#include "swapchainhandler.h"
#include "descriptorpool.h"
#include "descriptorlayout.h"

#include <iostream>
#include <vector>
#include <array>

/// @brief Class describing a Descriptor object, which is used to store a DescriptorPool and a DescriptorLayout.
///
/// The Descriptor class contains a DescriptorLayout the functionality to request, return and destroy a DescriptorPool. 
/// This class descripes the layout of the data that needs to be sent towards the shader and contains a pool for the objects that prepare the data.

class Descriptor {
	public:
		/// @brief The constructor for the Buffer class.
		Descriptor();
		Descriptor(VkDescriptorSetLayoutBinding* _descriptorLayout, int _descriptorLayoutSize, VkDescriptorPoolSize* _descriptorPool, int _descriptorPoolSize);
		/// @brief The deconstructor for the Buffer class.
		~Descriptor();

		/// @brief Get pointer to a new DescriptorPool object.
		/// @return A pointer to the DescriptorPool.
		DescriptorPool* getPool();

		/// @brief Free pointer to a new DescriptorPool object.
		/// @param A pointer to the DescriptorPool.
		void freePool(DescriptorPool* _pool);

		/// @brief Get reference to the VkDescriptorSetLayout.
		VkDescriptorSetLayout& getLayout();

	protected:
		std::vector<DescriptorPool*> _descriptorPools; ///< @brief Vector containing DescriptorPool's.
		DescriptorLayout* _layout; ///< @brief Pointer to DescriptorLayout.
	private:
		VkDescriptorPoolSize* _descriptorPool;
		int _descriptorPoolSize;
};
#endif