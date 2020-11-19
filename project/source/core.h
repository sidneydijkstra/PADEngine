
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "config.h"
#include "devicehandler.h"
#include "swapchainhandler.h"
#include "shader.h"
#include "renderer.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>
#include <vector>
#include <set>

#ifndef CORE_CLASS
#define CORE_CLASS



class Core {
    public:
        Core();
        ~Core();

        void run();

    private:
		DeviceHandler* _deviceHandler;
        SwapChainHandler* _swapChainHandler;
        Renderer* _renderer;

        void initVulkan();
        void createInstance();
        void createSurface();

        bool checkValidationLayerSupport();

        void initWindow();
        void loop();
        void cleanup();

        VkInstance _instance;

        VkSurfaceKHR _surface;

        GLFWwindow* _window;

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