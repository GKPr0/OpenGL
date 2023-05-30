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
		bool isTransparent() const { return mIsTransparent; }

	private:
		GLuint id;
		bool mIsTransparent;

		void load(const std::string& file);
	};
}