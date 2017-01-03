#pragma once
#include <glm/glm.hpp>
#include <Engine/ModelBatch.h>
#include <Engine/GLSLProgram.h>
#include "Pendulum.h"
#include <iostream>

class DoublePendulum
{
public:
	DoublePendulum();
	~DoublePendulum();

	void init(float initLength1, float initMass1, float initAngle1, float initLength2, float initMass2, float initAngle2, glm::vec3 initJointPos);
	void update();
	void draw(Engine::ModelBatch batch, GLuint texture, Engine::GLSLProgram& cp);
	void calcPosition();

	void colorTop(Engine::GLSLProgram& cp);
	void colorBottom(Engine::GLSLProgram& cp);

	// Setters
	void setMasses(float m1, float m2) { mass1 = m1; topS = mass1 / 2.0f;  mass2 = m2; botS = mass2 / 2.0f;}
	void setLengths(float l1, float l2) { length1 = l1; length2 = l2;  }
	void setAngles(float topAngle, float botAngle) { theta1 = topAngle ; theta2 = botAngle; trailPositions.clear(); }
	void setKAs(glm::vec4 top, glm::vec4 bot) { topKA = top; botKA = bot; }
	void setJointPosition(glm::vec3 newJointPos) { jointPos = newJointPos; }
	void setGravity(float g) { gravity = g; }

	// Getters
	float getLength1() { return length1; }
	float getLength2() { return length2; }
	void printAngles() { std::cout << theta1 << " " << theta2 << std::endl; }

private:
	void RungeKuttaMethod();
	float calcMotion(float t1, float t2, float w1, float w2, bool omega);
	void drawTrail(Engine::ModelBatch batch, GLint modelID, Engine::GLSLProgram& cp);

	float mass1;
	float length1;
	glm::vec3 mass1Pos;
	glm::vec4 topKA, topKD, topKS;
	float topS;


	float mass2;
	float length2;
	glm::vec3 mass2Pos;
	glm::vec4 botKA, botKD, botKS;
	float botS;

	glm::vec3 jointPos;

	float theta1;
	float theta2;
	float omega1;
	float omega2;
	float step;
	float gravity;
	float scale;
	float height;

	std::vector<glm::vec3> trailPositions;
};

