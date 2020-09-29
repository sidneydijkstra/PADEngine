
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "devicehandler.h"

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

        void initVulkan();
        void createInstance();
        void createSurface();
        void createSwapChain();
        void createImageView();

		// shader functions
		static std::vector<char> readFile(const std::string& filename);
        void createRenderPass();
        void createGraphicsPipeline();
		VkShaderModule createShaderModule(const std::vector<char>& code);

        // draw functions
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffers();
        void createSyncObjects();

        void drawFrame();

        bool checkValidationLayerSupport();

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& _capabilities);

        void initWindow();
        void loop();
        void cleanup();

        VkInstance _instance;
        VkPhysicalDevice _physicalDevice;
        VkDevice _device;
        VkQueue _graphicsQueue;
        VkQueue _presentQueue;

        VkRenderPass _renderPass;
        VkPipelineLayout _pipelineLayout;
        VkPipeline _graphicsPipeline;
        std::vector<VkFramebuffer> _swapChainFramebuffers;
        VkCommandPool _commandPool;
        std::vector<VkCommandBuffer> _commandBuffers;

        std::vector<VkSemaphore> _imageAvailableSemaphores;
        std::vector<VkSemaphore> _renderFinishedSemaphores;
        std::vector<VkFence> _inFlightFences;
        std::vector<VkFence> _imagesInFlight;
        size_t _currentFrame = 0;

        VkSurfaceKHR _surface;

        VkSwapchainKHR _swapChain;
        std::vector<VkImage> _swapChainImages;
        VkFormat _swapChainImageFormat;
        VkExtent2D _swapChainExtent;

        std::vector<VkImageView> _swapChainImageViews;

        GLFWwindow* _window;
        const uint32_t WIDTH = 800;
        const uint32_t HEIGHT = 600;

        const int MAX_FRAMES_IN_FLIGHT = 2;

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