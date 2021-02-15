/// @file descriptorpool.h
/// @brief Standalone header providing DescriptorPool functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef DESCRIPTORPOOL_CLASS
#define DESCRIPTORPOOL_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "devicehandler.h"
#include "swapchainhandler.h"

/// @brief Class describing a DescriptorPool object, which is used to store a VkDescriptorPool.
///
/// The DiscriptorPool class contains a pool that can be used to store data inside a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorSet.html">VkDescriptorSet</a> object. 
/// In order to initialize this pool it will need to be specified which data will be stored inside. 
/// This needs to be equated to the <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorSetLayout.html">VkDescriptorSetLayout</a> and the DescriptorLayout.

class DescriptorPool {
	public:
		/// @brief The constructor for the Buffer class.
		DescriptorPool();

		/// @brief The constructor for the Buffer class.
		/// @param _poolSize VkDescriptorPoolSize to use for this pool.
		DescriptorPool(VkDescriptorPoolSize _poolSize);

		/// @brief The constructor for the Buffer class.
		/// @param _size Size of VkDescriptorPoolSize.
		/// @param _layoutBinding Pointer VkDescriptorPoolSize to use for this pool.
		DescriptorPool(int _size, const VkDescriptorPoolSize* _poolSizeData);

		/// @brief The deconstructor for the Buffer class.
		~DescriptorPool();

		/// @brief Function to get a reference to current VkDescriptorPool.
		/// @return Reference to current VkDescriptorPool.
		VkDescriptorPool& getPool();

	protected:
		/// @brief Logic to setup VkDescriptorPool, can be overwritten to change VkDescriptorPool intern.
		/// @param _size Size of VkDescriptorPoolSize.
		/// @param _layoutBinding Pointer VkDescriptorPoolSize to use for this pool.
		virtual void setup(int _size, const VkDescriptorPoolSize* _poolSizeData);

	private:
		VkDescriptorPool _pool; ///< @brief VkDescriptorPool object containing pool.

};
#endif