

#ifndef CORE_CLASS
#define CORE_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "config.h"
#include "vulkanhandler.h"
#include "devicehandler.h"
#include "swapchainhandler.h"
#include "sequencemanager.h"
#include "scenemanager.h"
#include "input.h"
#include "time.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>
#include <vector>
#include <set>

class Core {
    public:
        Core();
        ~Core();

        void run();
        void cleanup();

    private:
        SequenceManager* _seqManager;
        Scene* _scene;

        void loop();
        void _run();

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};
#endif