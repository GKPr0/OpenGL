#pragma once

#include "Renderable.h"
#include "../base/Texture.h"
#include <vector>

namespace Engine
{
	class SkyBox : public Renderable{
	public:
		
		SkyBox(const std::vector<std::string> faces);
		virtual void render(Program& program) override;
	private:

		void loadTexture(const std::vector<std::string> faces);
		void create();

		GLuint textureId;
	};
}
