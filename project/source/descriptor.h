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
#include "descriptorpool.h"
#include "descriptorlayout.h"

#include <iostream>
#include <vector>
#include <array>

class Descriptor {
	public:
		Descriptor();
		~Descriptor();

		DescriptorPool* getPool();
		void freePool(DescriptorPool* _pool);
		VkDescriptorSetLayout getLayout();
	protected:
		std::vector<DescriptorPool*> _descriptorPools;
		DescriptorLayout* _layout;
	private:
};
#endif