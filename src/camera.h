
#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "config.h"
#include "input.h"
#include "time.h"

class Camera {
	public:
		Camera();
		~Camera();

		void update();
		void move3D(float _speed);

		glm::vec3 position; ///< @brief the position of the camera
		glm::vec3 front; ///< @brief the front of the camera
		glm::vec3 up; ///< @brief the up of the camera
		glm::vec3 right; ///< @brief the right of the camera

		float yaw; ///< @brief the yaw of the camera
		float pitch; ///< @brief the pitch of the camera
		float fov; ///< @brief the fov of the camera

	private:
		bool _firstClick;
		float lastX; ///< @brief the lastX of the camera
		float lastY; ///< @brief the lastY of the camera
};
#endif