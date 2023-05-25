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
		bool IsTransparent() const { return isTransparent; }

	private:
		GLuint id;
		bool isTransparent;

		void load(const std::string& file);
	};
}