#pragma once

#include <sstream>
#include <GL/glew.h> 
#include <GL/wglew.h> 

#include <GLFW/glfw3.h>


GLuint loadShader(const std::string vertexShader, const std::string fragShader);
std::string getShaderInfoLog(const GLuint obj);
std::string getProgramInfoLog(const GLuint obj);