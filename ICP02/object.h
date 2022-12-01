#pragma once
#include <iostream>
#include <GL/glew.h> 
#include <GL/wglew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Object {
	protected:
		GLuint shader;
		GLuint vao;

		glm::mat4 modelMatrix;

	public:
		Object(const std::string vertexShader, const std::string fragShader);
		virtual void draw();
		
		void setModelMatrix(const glm::mat4 modelMatrix);
		const glm::mat4 getModelMatrix();
};
