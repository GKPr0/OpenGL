#include "object.h"
#include "shaders.h"
#include "camera.h"
#include "globals.h"


Object::Object(const std::string vertexShader, const std::string fragShader)
{
	this->modelMatrix = glm::identity<glm::mat4>();
	this->shader = loadShader(vertexShader, fragShader);
}

void Object::setModelMatrix(const glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

const glm::mat4 Object::getModelMatrix()
{
	return this->modelMatrix;
}


void Object::draw() {
	Camera* camera = globals.camera;
	glUseProgram(this->shader);
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "uProj_m"), 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "uV_m"), 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "uM_m"), 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
	glBindVertexArray(this->vao);
}

