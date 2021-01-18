#include <cstdint>


#ifndef DESCRIPTOR_CLASS
#define DESCRIPTOR_CLASS

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

#include <iostream>
#include <vector>
#include <array>

class Descriptor {
	public:
		Descriptor();
		~Descriptor();

		VkDescriptorSetLayout getLayout();
		VkDescriptorPool getPool();
		void freePool(VkDescriptorPool _pool);

	private:
		VkDescriptorSetLayout _descriptorSetLayout;
		std::vector<VkDescriptorPool> _descriptorPools;

		//std::vector<VkDescriptorSet> _descriptorSets;

	private:
		void setupDescriptorLayout();
		VkDescriptorPool setupDescriptorPool();
		//void setupDescriptorSets();
};
#endif