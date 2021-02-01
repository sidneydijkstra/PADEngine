
#ifndef DESCRIPTORLAYOUT_CLASS
#define DESCRIPTORLAYOUT_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"

class DescriptorLayout {
	public:
		DescriptorLayout();
		DescriptorLayout(VkDescriptorSetLayoutBinding _layoutBinding);
		~DescriptorLayout();

		VkDescriptorSetLayout& getLayout();
	protected:
		virtual void setup(int _size, VkDescriptorSetLayoutBinding* _layoutBinding);

	private:
		VkDescriptorSetLayout _layout;
};
#endif