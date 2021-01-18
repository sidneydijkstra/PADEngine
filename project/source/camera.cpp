#include "camera.h"

Camera::Camera() {
	this->_firstClick = true;
	this->lastX = Config::WIDTH / 2.0;
	this->lastY = Config::HEIGHT / 2.0;

	position = glm::vec3(0.0f, 0.0f, 0.0f);
	front = glm::vec3(0.0f, -1.0f, 0.0f);
	up = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);

	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->fov = 70.0f;
}

void Camera::update() {
}

void Camera::move3D(float _speed) {
	// move camera wsad space shift
	float cameraSpeed = _speed * Time::getDeltaTime();
	if (Input::getKey(KeyCode::W)) {
		this->position += cameraSpeed * this->front;
	} 
	else if (Input::getKey(KeyCode::S)) {
		this->position -= cameraSpeed * this->front;
	}
	if(Input::getKey(KeyCode::A)) {
		this->position -= glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
	}
	else if(Input::getKey(KeyCode::D)) {
		this->position += glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
	}
	if(Input::getKey(KeyCode::Space)) {
		this->position += cameraSpeed * this->up;
	}
	else if(Input::getKey(KeyCode::LeftShift)) {
		this->position -= cameraSpeed * this->up;
	}

	// move camera front scroll
	float val = Input::getMouseScrollDelta().second;
	this->position += val * 2 * this->front;

	// move camera direction mouse
	if(Input::getMouseButton(0)){
		float xpos = Input::getMousePosition().first;
		float ypos = Input::getMousePosition().second;

		if (_firstClick) {
			this->lastX = xpos;
			this->lastY = ypos;
			_firstClick = false;
		}

		GLfloat xoffset = xpos - this->lastX;
		GLfloat yoffset = this->lastY - ypos; // Reversed since y-coordinates go from bottom to left
		this->lastX = xpos;
		this->lastY = ypos;

		GLfloat sensitivity = 0.10f;	// Change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		this->yaw += xoffset;
		this->pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (this->pitch > 89.0f)
			this->pitch = 89.0f;
		if (this->pitch < -89.0f)
			this->pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(-this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(-this->yaw)) * cos(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->pitch));
		this->front = glm::normalize(front);
	}else {
		_firstClick = true;
	}
}

Camera::~Camera() {
}