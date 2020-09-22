
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <optional>
#include <vector>

#ifndef CORE_CLASS
#define CORE_CLASS

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

class Core {
    public:
        Core();
        ~Core();

        void run();

    private:
        void initVulkan();
        void createInstance();
        void pickPhysicalDevice();
        void createLogicalDevice();

        bool checkValidationLayerSupport();
        bool isDeviceSuitable(VkPhysicalDevice _device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        void initWindow();
        void loop();
        void cleanup();

        VkInstance _instance;
        VkPhysicalDevice _physicalDevice;
        VkDevice _device;
        VkQueue _graphicsQueue;

        GLFWwindow* _window;
        const uint32_t WIDTH = 800;
        const uint32_t HEIGHT = 600;

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