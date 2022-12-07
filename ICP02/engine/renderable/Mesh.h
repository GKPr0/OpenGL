#pragma once
#include "Renderable.h"
#include <vector>

namespace Engine 
{
	struct MeshVertex 
	{
		glm::vec3 position;
		glm::vec2 texPosition;
		glm::vec3 normal;
	};

	class Mesh : public Renderable {
	public:
		Mesh(const std::vector<MeshVertex>& vertices, const std::vector<GLuint> indices);

		// Inherited via Renderable
		virtual void render(Program& program) override;

	private:
		std::vector<MeshVertex> vertices;
		std::vector<GLuint> indices;		
	};
}
