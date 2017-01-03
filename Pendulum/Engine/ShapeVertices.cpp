#include "ShapeVertices.h"
#include <iostream>

namespace Engine {

	GLuint sphere(std::vector<Vertex>& vertices, GLuint slices, float radius) {
		Vertex vertex;
		const int SPHERE_VERTS = (slices * VERTICES_QUAD * (slices - 2)) + (slices * VERTICES_TRI * 2);
		vertices.resize(SPHERE_VERTS);


		int index = 0;
		float phi_top = ((float)((slices / 2) - 1) / (float)(slices / 2)) * PI / 2.0;
		float phi_bot = -phi_top;

		for (int n = 0; n < slices; n++)
		{
			GLfloat const THETA_0 = 2 * PI * (float)n / (float)slices;
			GLfloat const THETA_1 = 2 * PI * (float)(n + 1) / (float)slices;

			vertices[index].setPosition(0.0, MODEL_TOP, 0.0);
			vertices[index].setUV(0.0, 0.0);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

			vertices[index].setPosition(cos(phi_top) * cos(THETA_0) * radius, sin(phi_top) * radius, cos(phi_top) * sin(THETA_0) * radius);
			vertices[index].setUV(THETA_0 / (2 * PI), -(phi_top - PI/2.0f) / PI);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

			vertices[index].setPosition(cos(phi_top) * cos(THETA_1) * radius, sin(phi_top) * radius, cos(phi_top) * sin(THETA_1) * radius);
			vertices[index].setUV(THETA_1 / (2 * PI), -(phi_top - PI / 2.0f) / PI);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);
		}

		for (int m = 1; m < slices - 1; m++)
		{
			float phi_0 = PI / 2.0 - m * PI / (float)slices;
			float phi_1 = PI / 2.0 - (m + 1) * PI / (float)slices;

			int num;
			for (int n = 0; n < slices; n++)
			{
				num = 0;
				float x = 0.0, y = 0.0, r = 0.5;

				GLfloat const THETA_0 = 2 * PI * (float)n / (float)slices;
				GLfloat const THETA_1 = 2 * PI * (float)(n + 1) / (float)slices;

				// top left
				vertices[index].setPosition(cos(phi_1)*cos(THETA_0) * radius, sin(phi_1) * radius, cos(phi_1)*sin(THETA_0) * radius);
				vertices[index].setUV(THETA_0 / (2 * PI), -(phi_1 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// top right
				vertices[index].setPosition(cos(phi_1)*cos(THETA_1) * radius, sin(phi_1) * radius, cos(phi_1)*sin(THETA_1) * radius);
				vertices[index].setUV(THETA_1 / (2 * PI), -(phi_1 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// bottom right
				vertices[index].setPosition(cos(phi_0)*cos(THETA_1) * radius, sin(phi_0) * radius, cos(phi_0)*sin(THETA_1) * radius);
				vertices[index].setUV(THETA_1 / (2 * PI), -(phi_0 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// top left
				vertices[index].setPosition(cos(phi_1)*cos(THETA_0) * radius, sin(phi_1) * radius, cos(phi_1)*sin(THETA_0) * radius);
				vertices[index].setUV(THETA_0 / (2 * PI), -(phi_1 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// bottom right
				vertices[index].setPosition(cos(phi_0)*cos(THETA_1) * radius, sin(phi_0) * radius, cos(phi_0)*sin(THETA_1) * radius);
				vertices[index].setUV(THETA_1 / (2 * PI), -(phi_0 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// bottom left
				vertices[index].setPosition(cos(phi_0)*cos(THETA_0) * radius, sin(phi_0) * radius, cos(phi_0)*sin(THETA_0) * radius);
				vertices[index].setUV(THETA_0 / (2 * PI), -(phi_0 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);
			}
		}

		for (int n = 0; n < slices; n++)
		{
			GLfloat const THETA_0 = 2 * PI * (float)n / (float)slices;
			GLfloat const THETA_1 = 2 * PI * (float)(n + 1) / (float)slices;

			vertices[index].setPosition(0.0, MODEL_BOT, 0.0);
			vertices[index].setUV(0.0, 1.0);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

			vertices[index].setPosition(cos(phi_bot) * cos(THETA_0) * radius, sin(phi_bot) * radius, cos(phi_bot) * sin(THETA_0) * radius);
			vertices[index].setUV(THETA_0 / (2 * PI), -(phi_bot - PI / 2.0f) / PI);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

			vertices[index].setPosition(cos(phi_bot) * cos(THETA_1) * radius, sin(phi_bot) * radius, cos(phi_bot) * sin(THETA_1) * radius);
			vertices[index].setUV(THETA_1 / (2 * PI), -(phi_bot - PI / 2.0f) / PI);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);
		}

		return SPHERE_VERTS;
	}

	glm::vec3 cubeVertices[8] = {
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),
		glm::vec3(0.5f,  0.5f,  0.5f),
		glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f,  0.5f, -0.5f),
		glm::vec3(0.5f,  0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f)
	};

	int face(int a, int b, int c, int d, std::vector<Vertex>& vertices, int index) {
		glm::vec3 u = cubeVertices[b] - cubeVertices[a];
		glm::vec3 v = cubeVertices[c] - cubeVertices[b];

		glm::vec3 normal = glm::normalize(glm::cross(u, v));

		vertices[index].setPosition(cubeVertices[a].x, cubeVertices[a].y, cubeVertices[a].z);
		vertices[index].setUV(1.0, 0.0);
		vertices[index++].setNormal(normal.x, normal.y, normal.z);

		vertices[index].setPosition(cubeVertices[b].x, cubeVertices[b].y, cubeVertices[b].z);
		vertices[index].setUV(0.0, 0.0);
		vertices[index++].setNormal(normal.x, normal.y, normal.z);

		vertices[index].setPosition(cubeVertices[c].x, cubeVertices[c].y, cubeVertices[c].z);
		vertices[index].setUV(0.0, 1.0);
		vertices[index++].setNormal(normal.x, normal.y, normal.z);

		vertices[index].setPosition(cubeVertices[a].x, cubeVertices[a].y, cubeVertices[a].z);
		vertices[index].setUV(1.0, 0.0);
		vertices[index++].setNormal(normal.x, normal.y, normal.z);

		vertices[index].setPosition(cubeVertices[c].x, cubeVertices[c].y, cubeVertices[c].z);
		vertices[index].setUV(0.0, 1.0);
		vertices[index++].setNormal(normal.x, normal.y, normal.z);

		vertices[index].setPosition(cubeVertices[d].x, cubeVertices[d].y, cubeVertices[d].z);
		vertices[index].setUV(1.0, 1.0);
		vertices[index++].setNormal(normal.x, normal.y, normal.z);

		return index;
	}

	void cube(std::vector<Vertex>& vertices) {
		Vertex vertex;
		vertices.resize(36);
		int index = 0;

		index = face(1, 0, 3, 2, vertices, index);
		index = face(2, 3, 7, 6, vertices, index);
		index = face(3, 0, 4, 7, vertices, index);
		index = face(6, 5, 1, 2, vertices, index);
		index = face(4, 5, 6, 7, vertices, index);
		index = face(5, 4, 0, 1, vertices, index);
	}

	GLuint cylinder(std::vector<Vertex>& vertices, GLuint slices, float radius) {
		Vertex vertex;
		const int CYLINDER_VERTS = (slices * VERTICES_QUAD * (slices - 2.0f)) + (slices * VERTICES_TRI * 2.0f);
		vertices.resize(CYLINDER_VERTS);


		int index = 0;
		float phi_top = ((float)((slices / 2.0f) - 1.0f) / (float)(slices / 2.0f)) * PI / 2.0f;
		float phi_bot = -phi_top;

		for (int n = 0; n < slices; n++)
		{
			GLfloat const t0 = 2 * PI * (float)n / (float)slices;
			GLfloat const t1 = 2 * PI * (float)(n + 1) / (float)slices;

			vertices[index].setPosition(0.0f, MODEL_TOP, 0.0f);
			vertices[index].setUV(0.5f, 0.5f);
			vertices[index++].setNormal(0.0f, 1.0f, 0.0f);

			vertices[index].setPosition(cos(t0) * radius, MODEL_TOP, sin(t0) * radius);
			vertices[index].setUV(0.5 * cos(t0) + 0.5, 0.5 * sin(t0) + 0.5);
			vertices[index++].setNormal(0.0f, 1.0f, 0.0f);

			vertices[index].setPosition(cos(t1) * radius, MODEL_TOP, sin(t1) * radius);
			vertices[index].setUV(0.5 * cos(t1) + 0.5, 0.5 * sin(t1) + 0.5);
			vertices[index++].setNormal(0.0f, 1.0f, 0.0f);
		}

		for (int n = 0; n < slices; n++)
		{

			GLfloat const t0 = 2 * PI * (float)n / (float)slices;
			GLfloat const t1 = 2 * PI * (float)(n + 1) / (float)slices;

			// a
			vertices[index].setPosition(cos(t0) * radius, MODEL_BOT, sin(t0) * radius);
			vertices[index].setUV(t0 / (2 * PI), MODEL_BOT);
			vertices[index++].setNormal(cos(t0) * radius, 0.0f, sin(t0) * radius);
			// b
			vertices[index].setPosition(cos(t1) * radius, MODEL_BOT, sin(t1) * radius);
			vertices[index].setUV(t0 / (2 * PI), MODEL_BOT);
			vertices[index++].setNormal(cos(t1) * radius, 0.0f, sin(t1) * radius);
			// c
			vertices[index].setPosition(cos(t1) * radius, MODEL_TOP, sin(t1) * radius);
			vertices[index].setUV(t1 / (2 * PI), MODEL_TOP);
			vertices[index++].setNormal(cos(t1) * radius, 0.0f, sin(t1) * radius);
			// a
			vertices[index].setPosition(cos(t0) * radius, MODEL_BOT, sin(t0) * radius);
			vertices[index].setUV(t0 / (2 * PI), MODEL_BOT);
			vertices[index++].setNormal(cos(t0) * radius, 0.0f, sin(t0) * radius);
			// c
			vertices[index].setPosition(cos(t1) * radius, MODEL_TOP, sin(t1) * radius);
			vertices[index].setUV(t1 / (2 * PI), MODEL_TOP);
			vertices[index++].setNormal(cos(t1) * radius, 0.0f, sin(t1) * radius);
			// d
			vertices[index].setPosition(cos(t0) * radius, MODEL_TOP, sin(t0) * radius);
			vertices[index].setUV(t0 / (2 * PI), MODEL_TOP);
			vertices[index++].setNormal(cos(t0) * radius, 0.0f, sin(t0) * radius);
		}


		for (int n = 0; n < slices; n++)
		{
			GLfloat const t0 = 2 * PI * (float)n / (float)slices;
			GLfloat const t1 = 2 * PI * (float)(n + 1) / (float)slices;

			vertices[index].setPosition(0.0f, MODEL_BOT, 0.0f);
			vertices[index].setUV(0.5f, 0.5f);
			vertices[index++].setNormal(0.0f, 1.0f, 0.0f);

			vertices[index].setPosition(cos(t1) * radius, MODEL_BOT, sin(t1) * radius);
			vertices[index].setUV(0.5 * cos(t1) + 0.5, 0.5 * sin(t1) + 0.5);
			vertices[index++].setNormal(0.0f, 1.0f, 0.0f);

			vertices[index].setPosition(cos(t0) * radius, MODEL_BOT, sin(t0) * radius);
			vertices[index].setUV(0.5 * cos(t0) + 0.5, 0.5 * sin(t0) + 0.5);
			vertices[index].setNormal(0.0f, 1.0f, 0.0f);
		}

		return CYLINDER_VERTS;
	}
}