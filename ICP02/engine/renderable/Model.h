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
		void camRelatedRender(Program& program, glm::vec3 cameraPos);

		std::vector<Mesh> getMeshes() const { return meshes; }

		void setIsCollisionChecked(const bool isCollisionChecked) { this->isCollisionChecked = isCollisionChecked; }

		bool isTransparent() const;

	private:
		void calculateBoundingBox();

		std::vector<Mesh> meshes;
		glm::vec3 bbMin;
		glm::vec3 bbMax;
		bool isCollisionChecked;
	};
}