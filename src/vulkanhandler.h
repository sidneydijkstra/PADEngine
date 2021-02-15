/// @file vulkanhandler.h
/// @brief Standalone header providing VulkanHandler functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#ifndef VULKANHANDLER_CLASS
#define VULKANHANDLER_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "config.h"

#include <iostream>
#include <vector>

namespace pad {

/// @brief Class describing a VulkanHandler, which handles window, surface and vulkan creation.
///
/// The VulkanHandler class is for initializing a <a href="https://www.glfw.org/docs/3.3/window_guide.html">GLFWwindow</a> object and a <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkInstance.html">VkInstance</a> which implements an instance of the Vulkan API. 
/// After the initialization of Vulkan and GLFW it`s window, the <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkSurfaceKHR.html">VkSurfaceKHR</a> object is created to use for rendering.

class VulkanHandler {
	public:
        /// @brief The constructor for the VulkanHandler class.
		VulkanHandler();
        /// @brief The deconstructor for the VulkanHandler class.
		~VulkanHandler();

        /// @brief Static get instance function, VulkanHandler is a singelton because we only need one instance.
        /// @return A pointer to VulkanHandler.
        static VulkanHandler* getInstance();

        /// @brief Static function to delete and cleanup the VulkanHandler.
        static void deleteInstance();

        /// @brief Initialisation function for VulkanHandler.
        void init();

        /// @brief Get the vulkan instance.
        /// @return The VkInstance.
        VkInstance getVkInstance();
        /// @brief Get the glfw window pointer.
        /// @return The GLFWwindow pointer.
        GLFWwindow* getWindow();
        /// @brief Get the vulkan surface.
        /// @return The VkSurfaceKHR.
        VkSurfaceKHR getSurface();

	private:
        VkInstance _vkInstance; ///< @brief VkInstance of VulkanHandler.
        GLFWwindow* _window; ///< @brief GLFWwindow pointer of VulkanHandler.
        VkSurfaceKHR _surface; ///< @brief VkSurfaceKHR of VulkanHandler.

        /// @brief Check valodation layer support for vulkan validation.
        bool checkValidationLayerSupport();

        const std::vector<const char*> _validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        #ifdef NDEBUG
                const bool _enableValidationLayers = false;
        #else
                const bool _enableValidationLayers = true;
        #endif
};

}

#endif