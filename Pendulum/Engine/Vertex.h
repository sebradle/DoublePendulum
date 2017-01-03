#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Engine {
	struct Vertex {
		glm::vec4 position;
		glm::vec2 uv;
		glm::vec3 normal;

		void setPosition(float x, float y, float z) {
			position.x = x;
			position.y = y;
			position.z = z;
			position.w = 1.0f;
		}

		void setUV(float u, float v) {
			uv.x = u;
			uv.y = v;
		}

		void setNormal(float x, float y, float z) {
			normal.x = x;
			normal.y = y;
			normal.z = z;
		}
	};
}