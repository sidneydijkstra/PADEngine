
#ifndef TIME_CLASS
#define TIME_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>
#include <string>

class Time {
	public:
		Time(void) = delete;
		Time(const Time&) = delete;
		Time(Time&&) = delete;

		~Time(void) = delete;

		static void update();
		
		static float getTime();
		static float getDeltaTime();
		static int getFps();

	private:
		inline static float _currentTime = 0;
		inline static float _lastTime = 0;
		inline static float _fps = 0;

		inline static float _lastFrame = 0;
		inline static float _deltaTime = 0;

		static void calculateDeltaTime();
		static void calculateFps();
};
#endif