#pragma once
#include <vector>
#include "Renderable.h"
#include "../base/Texture.h"

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
		Mesh() = default;
		Mesh(const std::vector<MeshVertex>& vertices, const std::vector<GLuint> indices, Texture* texture);

		virtual void render(Program& program) override;
		void camRelatedRender(Program& program, glm::vec3 cameraPos, glm::vec3 cameraDir);

		void setTexture(Texture* texture) { this->texture = texture; }
		Texture* getTexture() const { return texture; }

		void setIndices(const std::vector<GLuint>& indices) { this->indices = indices; }
		std::vector<GLuint> getIndices() const { return indices; }

		void setVertices(const std::vector<MeshVertex>& vertices) { this->vertices = vertices; }
		std::vector<MeshVertex> getVertices() const { return vertices; }

		static Mesh load(const std::string& path, Texture* texture);
	private:
		std::vector<MeshVertex> vertices;
		std::vector<GLuint> indices;	
		Texture* texture;
	};
}
