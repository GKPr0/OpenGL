#pragma once
#include <iostream>
#include <GL/glew.h>


namespace Engine 
{
	class Shader {
	public:
		Shader(const std::string& file, GLenum type);
		~Shader() { glDeleteShader(id); };
		
		static Shader createVertexShader(const std::string& file)
		{
			return Shader(file, GL_VERTEX_SHADER);
		}

		static Shader createFragmentShader(const std::string& file)
		{
			return Shader(file, GL_FRAGMENT_SHADER);
		}

		GLuint getId() const { return id; }
		GLenum getType() const { return type; }
		
	private:
		GLuint id;
		GLenum type;

		std::string loadSource(const std::string& file);
		std::string getShaderInfoLog(const GLuint id);
	};
}
