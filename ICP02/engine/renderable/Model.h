#pragma once
#include <vector>
#include "Mesh.h"

namespace Engine 
{
	class Model: public Renderable {
	public:
		Model(const std::string& path);

		void load(const std::string& path);
		
		virtual void render(Program& program) override;
	private:
		std::vector<Mesh> meshes;	
	};
}