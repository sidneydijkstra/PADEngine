/// @file core.h
/// @brief Standalone header providing Core functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021


#ifndef CORE_CLASS
#define CORE_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
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

namespace pad {

/// @brief Class describing a Core object, which handels the creation of necessary components and contains the main loop.
///
/// The Core class is for the initialization of the following classes: VulkanHandler, DeviceHandler, SwapChainHandler, the Input class and lastly the SequenceManager. 
/// These classes are initialized here because these classes control the rest of the engine with the Core class at its core. This class also contains the main loop that is called every tick. 
/// This loop updates the applications time, Input and through the SequenceManager class, the current Scene from the SceneManager as well.

class Core {
    public:
        Core();
        /// @brief The constructor for the Core class.
        ~Core();
        /// @brief The deconstructor for the Core class.

        /// @brief The standart run function to safely run the current scene.
        void run();

        /// @brief The cleanup function to clear all the managers.
        void cleanup();

    private:
        SequenceManager* _seqManager; ///< @brief The SequenceManager pointer.

        /// @brief The loop functions that updates glfw and runs the SequenceManager with the current scene.
        void loop();

        /// @brief The private run function to start the loop.
        void _run();

        /// @brief The framebuffer resize callback function for glfw resize callback, this handles window resizing.
	    /// @param window The pointer to GLFWwindow.
	    /// @param width The window width.
	    /// @param height The window height.
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};

}

#endif