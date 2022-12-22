#pragma once
#include <iostream>
#include <GL/glew.h>


namespace Engine
{
	class Texture {
	public:
		Texture(const std::string& file);
		~Texture() { glDeleteTextures(1, &id); }

		GLuint getId() const { return id; }
		
	private:
		GLuint id;

		void load(const std::string& file);
	};
}