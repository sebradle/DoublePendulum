#pragma once
#include <glm/glm.hpp>

namespace Engine {

	class Camera
	{
	public:
		Camera();

		void update(const glm::vec2& newMousePos);
		void moveFoward();
		void moveBackward();
		void strafeLeft();
		void strafeRight();
		void moveUp();
		void moveDown();

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjMatrix(float screenWidth, float screenHeight);

		glm::vec3 getPosition() { return position; }
		float getMoveSpeed() { return MOVE_SPEED; }
		
	private:
		const glm::vec3 UP;
		glm::vec3 right;
		const float MOVE_SPEED;
		glm::vec3 position;
		glm::vec3 viewDirec;
		glm::vec2 prevMousePos;
	};

}