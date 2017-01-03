#include "DoublePendulum.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Errors.h>
#include <iostream>



DoublePendulum::DoublePendulum() : gravity(9.81f), theta1(45.0f), theta2(45.0f)
{
}


DoublePendulum::~DoublePendulum()
{
}

void DoublePendulum::init(float initLength1, float initMass1, float initAngle1, float initLength2, float initMass2, float initAngle2, glm::vec3 initJointPos) {
	trailPositions.clear();
	setLengths(initLength1, initLength2);
	setMasses(initMass1, initMass2);
	setAngles(initAngle1, initAngle2);
	setJointPosition(initJointPos);
	omega1 = 0.0f;
	omega2 = 0.0f;
	step = 0.01;
	topKA = DEFAULT_TOP_COLOR;
	topKD = glm::vec4(0.0, 0.0, 0.0, 1.0);
	topKS = glm::vec4(1.0, 1.0, 1.0, 1.0);
	topS = mass1 / 2.0f;
	botKA = DEFAULT_BOT_COLOR;
	botKD = glm::vec4(0.0, 0.0, 0.0, 1.0);
	botKS = glm::vec4(1.0, 1.0, 1.0, 1.0);
	botS = mass2 / 2.0f;
	calcPosition();
}

void DoublePendulum::update() {
	RungeKuttaMethod();
	//RungeKuttaMethod();
	calcPosition();
}

void DoublePendulum::draw(Engine::ModelBatch batch, GLuint texture, Engine::GLSLProgram& cp) {
	GLint modelID = cp.getUniformLocation("model");

	// Draw Bar
	float rot =  M_PI / 2.0f;
	glm::mat4 joint = glm::translate(glm::mat4(1.0), jointPos);
	joint = glm::rotate(joint, rot,  glm::vec3(1.0f, 0.0f, 0.0f));
	joint = glm::scale(joint, glm::vec3(1.1f, 3.0f, 1.1f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &joint[0][0]);
	glUniform4fv(cp.getUniformLocation("ka"), 1, &glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)[0]);
	glUniform4fv(cp.getUniformLocation("kd"), 1, &glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)[0]);
	glUniform4fv(cp.getUniformLocation("ks"), 1, &glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)[0]);
	glUniform1f(cp.getUniformLocation("Shininess"), 5.5);
	batch.drawCylinder(texture);

	// Draw Top Pendulum
	glm::vec3 midpoint((0.0f - mass1Pos.x) / 2 , (0.0f - mass1Pos.y) / 2, (0.0f - mass1Pos.z) / 2);
	glm::mat4 model = glm::translate(glm::mat4(1.0), jointPos);
	model = glm::translate(model, -midpoint * 2.0f);
	model = glm::rotate(model, theta1, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, length1 * 2.0f, 1.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	colorTop(cp);
	batch.drawCylinder(texture); 

	model = glm::translate(glm::mat4(1.0), jointPos);
	model = glm::translate(model, glm::vec3(mass1Pos.x * 2.0f, mass1Pos.y * 2.0f, mass1Pos.z * 2.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	batch.drawSphere(texture);

	// Draw Bottom Pendulum
	colorBottom(cp);
	glm::vec3 midpoint2( mass1Pos.x + (-(mass1Pos.x - mass2Pos.x) / 2.0f), mass1Pos.y + (-(mass1Pos.y - mass2Pos.y) / 2.0f), 0.0f);
	model = glm::translate(glm::mat4(1.0), jointPos);
	model = glm::translate(model, midpoint2 * 2.0f);
	model = glm::rotate(model, theta2, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, length2 * 2.0f, 1.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	batch.drawCylinder(texture);

	model = glm::translate(glm::mat4(1.0), jointPos);
	model = glm::translate(model, glm::vec3(mass2Pos.x * 2.0f, mass2Pos.y * 2.0f, mass2Pos.z * 2.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	batch.drawSphere(texture);

	// Draw Trailine
	drawTrail(batch, modelID, cp);
}

void DoublePendulum::calcPosition() {
	mass1Pos.x = 0.0f + length1 * sin(theta1);
	mass1Pos.y = 0.0f - length1 * cos(theta1);

	mass2Pos.x = mass1Pos.x + length2 * sin(theta2);
	mass2Pos.y = mass1Pos.y - length2 * cos(theta2);

	trailPositions.push_back(glm::vec3(mass2Pos.x, mass2Pos.y, mass2Pos.z));
}

void DoublePendulum::colorTop(Engine::GLSLProgram& cp) {
	glUniform4fv(cp.getUniformLocation("ka"), 1, &topKA[0]);
	glUniform4fv(cp.getUniformLocation("kd"), 1, &topKD[0]);
	glUniform4fv(cp.getUniformLocation("ks"), 1, &topKS[0]);
	glUniform1f(cp.getUniformLocation("Shininess"), topS);
}


void DoublePendulum::colorBottom(Engine::GLSLProgram& cp) {
	glUniform4fv(cp.getUniformLocation("ka"), 1, &botKA[0]);
	glUniform4fv(cp.getUniformLocation("kd"), 1, &botKD[0]);
	glUniform4fv(cp.getUniformLocation("ks"), 1, &botKS[0]);
	glUniform1f(cp.getUniformLocation("Shininess"), botS);
}

void DoublePendulum::RungeKuttaMethod() {

	float kTheta1[4];
	float kTheta2[4];
	float kOmega1[4];
	float kOmega2[4];

	kTheta1[0] = omega1;
	kTheta2[0] = omega2;
	kOmega1[0] = calcMotion(theta1, theta2, omega1, omega2, true);
	kOmega2[0] = calcMotion(theta1, theta2, omega1, omega2, false);

	kTheta1[1] = omega1 + (step*0.5f*kOmega1[0]);
	kTheta2[1] = omega2 + (step*0.5f*kOmega2[0]);
	kOmega1[1] = calcMotion(theta1 + (step*0.5f*kTheta1[0]), theta2 + (step*0.5f*kTheta2[0]), omega1 + (step*0.5f*kOmega1[0]), omega2 + (step*0.5f*kOmega2[0]), true);
	kOmega2[1] = calcMotion(theta1 + (step*0.5f*kTheta1[0]), theta2 + (step*0.5f*kTheta2[0]), omega1 + (step*0.5f*kOmega1[0]), omega2 + (step*0.5f*kOmega2[0]), false);

	kTheta1[2] = omega1 + (step*0.5f*kOmega1[1]);
	kTheta2[2] = omega2 + (step*0.5f*kOmega2[1]);
	kOmega1[2] = calcMotion(theta1 + (step*0.5f*kTheta1[1]), theta2 + (step*0.5f*kTheta2[1]), omega1 + (step*0.5f*kOmega1[1]), omega2 + (step*0.5f*kOmega2[1]), true);
	kOmega2[2] = calcMotion(theta1 + (step*0.5f*kTheta1[1]), theta2 + (step*0.5f*kTheta2[1]), omega1 + (step*0.5f*kOmega1[1]), omega2 + (step*0.5f*kOmega2[1]), false);

	kTheta1[3] = omega1 + (step*kOmega1[2]);
	kTheta2[3] = omega2 + (step*kOmega2[2]);
	kOmega1[3] = calcMotion(theta1 + (step*kTheta1[2]), theta2 + (step*kTheta2[2]), omega1 + (step*kOmega1[2]), omega2 + (step*kOmega2[2]), true);
	kOmega2[3] = calcMotion(theta1 + (step*kTheta1[2]), theta2 + (step*kTheta2[2]), omega1 + (step*kOmega1[2]), omega2 + (step*kOmega2[2]), false);

	theta1 = theta1 + ((kTheta1[0] + (2.0f * kTheta1[1]) + (2.0f * kTheta1[2]) + kTheta1[3]) *(step/6.0f));
	theta2 = theta2 + ((kTheta2[0] + (2.0f * kTheta2[1]) + (2.0f * kTheta2[2]) + kTheta2[3]) *(step/6.0f));
	omega1 = omega1 + ((kOmega1[0] + (2.0f * kOmega1[1]) + (2.0f * kOmega1[2]) + kOmega1[3]) *(step/6.0f));
	omega2 = omega2 + ((kOmega2[0] + (2.0f * kOmega2[1]) + (2.0f * kOmega2[2]) + kOmega2[3]) *(step/6.0f));
																	
	
	if (theta1 > 2 * M_PI) {
		theta1 -= 2 * M_PI;
	}
	if (theta2 > 2 * M_PI) {
		theta2 -= 2 * M_PI;
	}
	if (theta1 < -2 * M_PI) {
		theta1 += 2 * M_PI;
	}
	if (theta2 < -2 * M_PI) {
		theta2 += 2 * M_PI;
	}
}

float DoublePendulum::calcMotion(float t1, float t2, float w1, float w2, bool omega) {
	float delta = t1 - t2;
	float numerator = 0.0f;
	float denominator = (2 * mass1 + mass2 - mass2*cos(2.0f * t1 - 2.0f * t2));

	if (omega) {
		numerator = -gravity*(2.0f*mass1 + mass2)*sin(t1) - mass2*gravity*sin(t1 - 2.0f*t2) - 2.0f*sin(delta)*mass2*(w2*w2*length2 + w1*w2*length1*cos(delta));
		denominator *= length1;
	}
		
	else{
		numerator = 2.0f*sin(delta)*(w1*w1*length1*(mass1 + mass2) + gravity*(mass1 + mass2)*cos(t1) + w2*w2*length2*mass2*cos(delta));
		denominator *= length2;
	} 

	if (denominator == 0.0f) {
		Engine::fatalError("Cannot divide by zero!");
	}
	return numerator / denominator;
}

void DoublePendulum::drawTrail(Engine::ModelBatch batch, GLint modelID, Engine::GLSLProgram& cp) {
	glm::vec4 trailColor = botKA;
	trailColor.a = 0.2f;
	glUniform4fv(cp.getUniformLocation("ka"), 1, &trailColor[0]);
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(jointPos.x, jointPos.y, jointPos.z));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	batch.drawTrailLine(trailPositions);
}
