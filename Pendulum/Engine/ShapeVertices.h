#pragma once
#include <vector>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
	extern GLuint sphere(std::vector<Vertex>& vertices, GLuint slices, float radius);
	extern void cube(std::vector<Vertex>& vertices);
	extern int face(int a, int b, int c, int d, std::vector<Vertex>& vertices, int index);
	extern GLuint cylinder(std::vector<Vertex>& vertices, GLuint numVertices, float radius);

	const int VERTICES_QUAD = 6;
	const int VERTICES_TRI = 3;
	const float PI = 3.14159265358979323846;
	const float MODEL_TOP = 0.5;
	const float MODEL_BOT = -0.5;

	
}