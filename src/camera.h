/// @file camera.h
/// @brief Standalone header providing camera functionality.
/// @author Sidney Dijkstra
/// @version 1.0.0
/// @date 02/01/2021

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

//namespace pad {

/// @brief Enumeration specifying the type of the camera, either 2D or 3D.
enum class Type {
	ORTHOGRAPHIC, PERSPECTIVE
};

/// @brief Class describing a Buffer object, which is used to store variables in vulkan buffer objects.
///
/// The camera class is the object through which the player views the world. 
/// The Camera object can be set when initializing a Scene since the camera is created with the scene. 
/// Here the Camera can be set to orthographic which means a 2D view or perspective which creates a 3D scene.

class Camera {
	public:
		/// @brief The constructor for the Camera class.
		/// @param The given type of camera to initialize.
		Camera(Type type = Type::PERSPECTIVE);
		/// @brief The deconstructor for the Camera class.
		~Camera();

		/// @brief The update function for the Camera class.
		void update();

		/// @brief The function to move the Camera using mouse and keyboard.
		/// @param _speed The move speed of the Camera.
		void move3D(float _speed);
		
		Type getType();

		glm::vec3 position; ///< @brief the position of the Camera
		glm::vec3 front; ///< @brief the front of the Camera
		glm::vec3 up; ///< @brief the up of the Camera
		glm::vec3 right; ///< @brief the right of the Camera

		float yaw; ///< @brief the yaw of the Camera
		float pitch; ///< @brief the pitch of the Camera
		float fov; ///< @brief the fov of the Camera

	private:
		Type _type;
		bool _firstClick;
		float lastX; ///< @brief the lastX of the Camera
		float lastY; ///< @brief the lastY of the Camera
};

//}
#endif