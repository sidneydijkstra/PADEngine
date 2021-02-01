
#ifndef DESCRIPTORPOOL_CLASS
#define DESCRIPTORPOOL_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"

class DescriptorPool {
	public:
		DescriptorPool();
		DescriptorPool(VkDescriptorPoolSize _poolSize);
		DescriptorPool(int _size, const VkDescriptorPoolSize* _poolSizeData);
		~DescriptorPool();

		VkDescriptorPool getPool();
	protected:
		virtual void setup(int _size, const VkDescriptorPoolSize* _poolSizeData);

	private:
		VkDescriptorPool _pool;

};
#endif