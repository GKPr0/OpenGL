#pragma once
#include <vector>
#include "Mesh.h"

namespace Engine 
{
	class Model: public Renderable {
	public:
		Model(const std::string& path, Texture* texture);

		void load(const std::string& path, Texture* texture);
		
		virtual void render(Program& program) override;

		Texture* getTexture() const { return texture; }
	private:
		std::vector<Mesh> meshes;
		Texture* texture;
	};
}