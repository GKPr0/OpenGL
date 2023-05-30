#pragma once
#include <vector>
#include "Mesh.h"

namespace Engine 
{
	class Model: public Renderable {
	public:
		Model(const std::string& path, Texture* texture, const bool isCollisionAllowed = true);

		void load(const std::string& path, Texture* texture);
		bool checkCollision(const glm::vec3& position) const;

		virtual void translate(const glm::vec3& translate) override;
		virtual void scale(const glm::vec3& vec) override;
		virtual void rotate(const float& angle, const glm::vec3& vec) override;

		virtual void render(Program& program) override;

		std::vector<Mesh> getMeshes() const { return meshes; }

		void setIsCollisionChecked(const bool isCollisionChecked) { this->isCollisionChecked = isCollisionChecked; }

		Texture* getTexture() const { return texture; }
	private:
		void calculateBoundingBox();


		std::vector<Mesh> meshes;
		Texture* texture;
		glm::vec3 bbMin;
		glm::vec3 bbMax;
		bool isCollisionChecked;
	};
}