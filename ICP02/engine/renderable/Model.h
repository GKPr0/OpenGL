#pragma once
#include <vector>
#include "Mesh.h"

namespace Engine 
{
	class Model: public Renderable {
	public:
		Model(const std::string& path, Texture* texture);

		void load(const std::string& path, Texture* texture);
		bool checkCollision(const glm::vec3& position) const;

		virtual void translate(const glm::vec3& translate) override;
		virtual void scale(const glm::vec3& vec) override;
		virtual void rotate(const float& angle, const glm::vec3& vec) override;

		virtual void render(Program& program) override;

		Texture* getTexture() const { return texture; }
	private:
		void calculateBoundingBox();

		std::vector<Mesh> meshes;
		Texture* texture;
		glm::vec3 aabbMin;
		glm::vec3 aabbMax;
	};
}