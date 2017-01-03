#include "Scene.h"



Scene::Scene() : floorKA(DEFAULT_FLOOR_COLOR), bgColor(DEFAULT_BACKGROUND_COLOR), floor(glm::vec3(0.0f, 0.0f, 0.0f))
{
}


Scene::~Scene()
{
}

void Scene::init(glm::vec4 floorColor, glm::vec4 backGroundColor, glm::vec3 floorDepth) {
	floorKA = floorColor;
	bgColor = backGroundColor;
	floor = floorDepth;
}

void Scene::set(glm::vec4 backgroundColor, glm::vec4 floorColor) {
	floorKA = floorColor;
	bgColor = backgroundColor;
}

void Scene::draw(Engine::ModelBatch batch, GLuint texture, Engine::GLSLProgram& cp) {
	// Back Ground
	glClearColor(bgColor.x, bgColor.y, bgColor.z, bgColor.w);

	// Floor
	glm::vec4 whiteSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 blackDiffuse(0.0f, 0.0f, 0.0, 1.0f);
	float matte = 3.0f;

	glUniform4fv(cp.getUniformLocation("ka"), 1, &floorKA[0]);
	glUniform4fv(cp.getUniformLocation("kd"), 1, &whiteSpecular[0]);
	glUniform4fv(cp.getUniformLocation("ks"), 1, &blackDiffuse[0]);
	glUniform1f(cp.getUniformLocation("Shininess"), matte);

	glm::mat4 model = glm::translate(glm::mat4(1.0), floor);
	model = glm::scale(model, glm::vec3(1000.0f, 0.1f, 1000.0f));
	glUniformMatrix4fv(cp.getUniformLocation("model"), 1, GL_FALSE, &model[0][0]);
	batch.drawCube(texture);
}