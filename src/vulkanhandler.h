
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

class VulkanHandler {
	public:
		VulkanHandler();
		~VulkanHandler();
        static VulkanHandler* getInstance();
        void init();
        static void deleteInstance();

        VkInstance getVkInstance();
        GLFWwindow* getWindow();
        VkSurfaceKHR getSurface();

	private:
        VkInstance _vkInstance;
        GLFWwindow* _window;
        VkSurfaceKHR _surface;

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
#endif