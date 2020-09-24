
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


#include <iostream>
#include <algorithm>
#include <optional>
#include <vector>
#include <set>

#ifndef CORE_CLASS
#define CORE_CLASS

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();;
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Core {
    public:
        Core();
        ~Core();

        void run();

    private:
        void initVulkan();
        void createInstance();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createSwapChain();
        void createImageView();

        bool checkValidationLayerSupport();
        bool checkDeviceExtensionSupport(VkPhysicalDevice _device);
        bool isDeviceSuitable(VkPhysicalDevice _device);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice _device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice _device);

        void initWindow();
        void loop();
        void cleanup();

        VkInstance _instance;
        VkPhysicalDevice _physicalDevice;
        VkDevice _device;
        VkQueue _graphicsQueue;
        VkQueue _presentQueue;

        VkSurfaceKHR _surface;

        VkSwapchainKHR _swapChain;
        std::vector<VkImage> _swapChainImages;
        VkFormat _swapChainImageFormat;
        VkExtent2D _swapChainExtent;

        std::vector<VkImageView> _swapChainImageViews;

        GLFWwindow* _window;
        const uint32_t WIDTH = 800;
        const uint32_t HEIGHT = 600;

        const std::vector<const char*> _validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> _deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        #ifdef NDEBUG
                const bool _enableValidationLayers = false;
        #else
                const bool _enableValidationLayers = true;
        #endif

        
};
#endif