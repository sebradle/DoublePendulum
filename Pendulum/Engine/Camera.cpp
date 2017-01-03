#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
	Camera::Camera() :	viewDirec(0.0f, 0.0f, -1.0f),
						UP(0.0f, 1.0f, 0.0f),
						MOVE_SPEED(1.0f),
						position(0.0f, 0.0f, 3.0f)
	{
	}
	
	void Camera::update(const glm::vec2& newMousePos) {
		glm::vec2 mouseDelta = newMousePos - prevMousePos;

		if (glm::length(mouseDelta) > 50.0f) {
			prevMousePos = newMousePos;
			return;
		}

		const float ROTATIONAL_SPEED = 0.025f;
		right = glm::cross(viewDirec, UP);
		viewDirec = glm::mat3(	glm::rotate(glm::mat4(1.0f), -mouseDelta.x * ROTATIONAL_SPEED, UP) * 
								glm::rotate(glm::mat4(1.0f), -mouseDelta.y * ROTATIONAL_SPEED, right)) * viewDirec;

		prevMousePos = newMousePos;
	}


	void Camera::moveFoward() {
		position += MOVE_SPEED * viewDirec;
	}

	void Camera::moveBackward() {

		position += -MOVE_SPEED * viewDirec;
	}

	void Camera::strafeLeft() {
		position += -MOVE_SPEED * right;
	}

	void Camera::strafeRight() {
		position += MOVE_SPEED * right;
	}

	void Camera::moveUp() {
		position += MOVE_SPEED * UP;
	}

	void Camera::moveDown() {
		position += -MOVE_SPEED * UP;
	}


	glm::mat4 Camera::getViewMatrix() const {
		return glm::lookAt(position, position + viewDirec, UP);
	}

	glm::mat4 Camera::getProjMatrix(float screenWidth, float screenHeight){
		return glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.1f, 500.0f);
	}
}