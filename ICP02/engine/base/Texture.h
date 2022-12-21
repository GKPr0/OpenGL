#pragma once
#include <iostream>
#include <GL/glew.h>


namespace Engine
{
	class Texture {
		GLuint id;

		void load(const std::string& file);

	public:
		Texture(const std::string& file);

		GLuint getId() const { return id; }
	};
}