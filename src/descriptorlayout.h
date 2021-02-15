/// @file descriptorlayout.h
/// @brief Standalone header providing DescriptorLayout functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef DESCRIPTORLAYOUT_CLASS
#define DESCRIPTORLAYOUT_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"

/// @brief Class describing a DescriptorLayout object, which is used to store a VkDescriptorSetLayout.
///
/// In order to send information to the Shader the layout of the data send needs to be determined in advance.
/// Within the DescriptorLayout class a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorSetLayout.html">VkDescriptorSetLayout</a> is created with the layout for the data. 
/// In OpenGL it is possible to send data to the shader in any layout at any moment. In Vulkan however this is not possible. 
/// In Vulkan it is required to specify what data will be sent where.
class DescriptorLayout {
	public:
		/// @brief The constructor for the DescriptorLayout class.
		DescriptorLayout();

		/// @brief The constructor for the DescriptorLayout class.
		/// @param _layoutBinding The descriptor set layout binding to use for this layout.
		DescriptorLayout(VkDescriptorSetLayoutBinding _layoutBinding);

		/// @brief The constructor for the DescriptorLayout class.
		/// @param _size The size of the set layout.
		/// @param _layoutBinding The descriptor set layout binding to use for this layout.
		DescriptorLayout(int _size, VkDescriptorSetLayoutBinding* _layoutBinding);

		/// @brief The deconstructor for the DescriptorLayout class.
		~DescriptorLayout();

		/// @brief Function to get a reference to current VkDescriptorSetLayout.
		/// @return Reference to current VkDescriptorSetLayout.
		VkDescriptorSetLayout& getLayout();

	protected:
		/// @brief Logic to setup DescriptorLayout, can be overwritten to change DescriptorLayout intern.
		/// @param _size Size of VkDescriptorSetLayoutBinding.
		/// @param _layoutBinding Pointer VkDescriptorSetLayoutBinding to use for this layout.
		virtual void setup(int _size, VkDescriptorSetLayoutBinding* _layoutBinding);

	private:
		VkDescriptorSetLayout _layout; ///< @brief VkDescriptorSetLayout object containing layout.
};
#endif