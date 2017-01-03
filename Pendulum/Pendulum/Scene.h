#pragma once
#include <Engine/ModelBatch.h>
#include <Engine/GLSLProgram.h>
#include <Engine/GLSLProgram.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Pendulum.h"

class Scene
{
public:
	Scene();
	~Scene();

	void init(glm::vec4 floorColor, glm::vec4 backGroundColor, glm::vec3 floorDepth);
	void set(glm::vec4 backgroundColor, glm::vec4 floorColor);
	void draw(Engine::ModelBatch batch, GLuint texture, Engine::GLSLProgram& cp);

private:
	glm::vec4 floorKA;
	glm::vec4 bgColor;
	glm::vec3 floor;
};

