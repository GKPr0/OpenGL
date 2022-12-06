#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine {

	void initGlew();

	void initGlfw();

	void errCallback(int error, const char* description);

	void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
}

