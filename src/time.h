
#ifndef TIME_CLASS
#define TIME_CLASS
/// @file time.h
/// @brief Standalone header providing Time functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>
#include <string>

namespace pad {

/// @brief Class describing a Time object, which handles frame/deltatime calculations and standart time functions using glfw and also calculates the frames per second.
class Time {
	public:
		Time(void) = delete;
		Time(const Time&) = delete;
		Time(Time&&) = delete;
		~Time(void) = delete;

		/// @brief Update function for Time.
		static void update();

		/// @brief Get current time.
		/// @return Current time.
		static float getTime();

		/// @brief Get current deltatime.
		/// @return Current deltatime.
		static float getDeltaTime();

		/// @brief Get current fps.
		/// @return Current fps.
		static int getFps();

	private:
		inline static float _currentTime = 0; ///< @brief Current time vairable.
		inline static float _lastTime = 0; ///< @brief Last fps vairable.
		inline static float _fps = 0; ///< @brief Fps vairable.

		inline static float _lastFrame = 0; ///< @brief Last frame time vairable.
		inline static float _deltaTime = 0; ///< @brief Deltatime vairable.

		/// @brief Calculate current deltatime.
		static void calculateDeltaTime();

		/// @brief Calculate current fps.
		static void calculateFps();
};

}

#endif