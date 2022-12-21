#pragma once
#include <iostream>
#include <GL/glew.h>


namespace Engine 
{
	class Shader {
		GLuint id;
		GLenum type;

		Shader(const std::string& file, GLenum type);

		std::string loadSource(const std::string& file);
		std::string getShaderInfoLog(const GLuint id);

	public:
		static Shader createVertexShader(const std::string& file)
		{
			return Shader(file, GL_VERTEX_SHADER);
		}

		static Shader createFragmentShader(const std::string& file)
		{
			return Shader(file, GL_FRAGMENT_SHADER);
		}

		void clear() const { glDeleteShader(id); }

		GLuint getId() const { return id; }
		GLenum getType() const { return type; }
	};
}
