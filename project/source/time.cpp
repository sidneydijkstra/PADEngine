#include "time.h"

void Time::update() {
	Time::calculateDeltaTime();
	Time::calculateFps();
}

float Time::getTime() {
	return Time::_currentTime;
}

float Time::getDeltaTime() {
	return Time::_deltaTime;
}

int Time::getFps() {
	return Time::_fps;
}

void Time::calculateDeltaTime() {
	float _currentFrame = glfwGetTime();
	Time::_deltaTime = _currentFrame - Time::_lastFrame;
	Time::_lastFrame = _currentFrame;
}

void Time::calculateFps() {
	Time::_currentTime = glfwGetTime();
	Time::_fps++;
	if (Time::_currentTime - Time::_lastTime >= 1) {
		//std::cout << "fps: " << std::to_string(Time::_fps) << std::endl;
		Time::_lastTime = glfwGetTime();
		Time::_fps = 0;
	}
}
