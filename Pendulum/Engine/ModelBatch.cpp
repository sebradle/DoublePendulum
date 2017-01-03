#include "ModelBatch.h"
#include <algorithm>
#include <iostream>

#include "imgui/imgui.h"

namespace Engine {

	ModelBatch::ModelBatch() : mVAO(0), mVBO(0)
	{
	}


	ModelBatch::~ModelBatch()
	{
	}

	void ModelBatch::init() {


		if (mVAO == 0) {
			glGenVertexArrays(1, &mVAO);
		}
		glBindVertexArray(mVAO);

		if (mVBO == 0) {
			glGenBuffers(1, &mVBO);
		}
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		cube(mCubeBuffer);
		mCylinderVertices = cylinder(mCylinderBuffer, 64, 0.1f);
		mSphereVertices = sphere(mSphereBuffer, 64, 0.5f);

		SPHERE_OFFSET = 0;
		CYLINDER_OFFSET = SPHERE_OFFSET + (mSphereBuffer.size() * sizeof(Vertex));
		CUBE_OFFSET = CYLINDER_OFFSET + (mCylinderBuffer.size() * sizeof(Vertex));

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, (mCubeBuffer.size() * sizeof(Vertex)) +
			(mCylinderBuffer.size() * sizeof(Vertex)) +
			(mSphereBuffer.size() * sizeof(Vertex)), NULL, GL_STATIC_DRAW);


		glBufferSubData(GL_ARRAY_BUFFER, SPHERE_OFFSET, mSphereBuffer.size() * sizeof(Vertex), mSphereBuffer.data());
		glBufferSubData(GL_ARRAY_BUFFER, CYLINDER_OFFSET, mCylinderBuffer.size() * sizeof(Vertex), mCylinderBuffer.data());
		glBufferSubData(GL_ARRAY_BUFFER, CUBE_OFFSET, mCubeBuffer.size() * sizeof(Vertex), mCubeBuffer.data());

		glBindVertexArray(0);
	}

	void ModelBatch::drawSphere(GLuint texture) {
		glBindVertexArray(mVAO);

		glBindTexture(GL_TEXTURE_2D, texture);

		auto vertexOffset = SPHERE_OFFSET + offsetof(Vertex, position);
		auto uvOffset = SPHERE_OFFSET + offsetof(Vertex, uv);
		auto normalOffset = SPHERE_OFFSET + offsetof(Vertex, normal);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) vertexOffset);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) uvOffset);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) normalOffset);

		glDrawArrays(GL_TRIANGLES, 0, mSphereVertices);
		 
		glBindVertexArray(0);
	}

	void ModelBatch::drawCylinder(GLuint texture) {
		glBindVertexArray(mVAO);

		glBindTexture(GL_TEXTURE_2D, texture);

		auto vertexOffset = CYLINDER_OFFSET + offsetof(Vertex, position);
		auto uvOffset = CYLINDER_OFFSET + offsetof(Vertex, uv);
		auto normalOffset = CYLINDER_OFFSET + offsetof(Vertex, normal);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)vertexOffset);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)uvOffset);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)normalOffset);

		glDrawArrays(GL_TRIANGLES, 0, mCylinderVertices);

		glBindVertexArray(0);
	}


	void ModelBatch::drawCube(GLuint texture) {
		glBindVertexArray(mVAO);

		glBindTexture(GL_TEXTURE_2D, texture);

		auto vertexOffset = CUBE_OFFSET + offsetof(Vertex, position);
		auto uvOffset = CUBE_OFFSET + offsetof(Vertex, uv);
		auto normalOffset = CUBE_OFFSET + offsetof(Vertex, normal);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)vertexOffset);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)uvOffset);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)normalOffset);

		glDrawArrays(GL_TRIANGLES, 0, mCubeVertices);

		glBindVertexArray(0);
	}

	void ModelBatch::drawOrbit(float distance, float scale) {
		glLineWidth(1.0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		for (float angle = 0.0f; angle < 2 * PI; angle += 0.01f) {
			glVertex3f(cos(angle) * distance, 0.0f, sin(angle) * distance);
		}
		glEnd();
	}

	void ModelBatch::drawTrailLine(std::vector<glm::vec3>& trailPos) {
		glLineWidth(1.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		
		std::vector<glm::vec3>::iterator it;
		it = trailPos.begin();

		
		glBegin(GL_LINES);
		while (it < trailPos.end()) {
			it++;
			if (it == trailPos.end()) {
				continue;
			}
			it--;
			glVertex3f(it->x, it->y, it->z);
			it++;
			glVertex3f(it->x, it->y, it->z);
		}
		glEnd();
		

	}
}