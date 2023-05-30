#include "Model.h"
#include "../support/OBJloader.h"
#include <map>

namespace Engine {
	Model::Model(const std::string& path, Texture* texture, const bool isCollisionChecked) : isCollisionChecked(isCollisionChecked)
	{
		load(path, texture);
	}

	void Model::load(const std::string& path, Texture* texture)
	{
		Mesh mesh = Mesh::load(path, texture);
		meshes.push_back(mesh);

		this->texture = texture;
		calculateBoundingBox();
	}

	void Model::translate(const glm::vec3& translate)
	{
		mPosition += translate;
		calculateBoundingBox();
	}

	void Model::scale(const glm::vec3& vec)
	{
		mScale = vec;
		calculateBoundingBox();
	}

	void Model::rotate(const float& angle, const glm::vec3& vec)
	{
		mRotation = glm::rotate(mRotation, glm::radians(angle), vec);
		calculateBoundingBox();
	}

	void Model::calculateBoundingBox()
	{
		glm::mat4x4 modelMatrix = getModelMatrix();

		bbMin = bbMax = modelMatrix * glm::vec4(meshes[0].getVertices()[0].position, 1.0);
		for (auto mesh : meshes)
		{
			for (const auto& vertex : mesh.getVertices())
			{
				glm::vec3 transformedPosition = modelMatrix * glm::vec4(vertex.position, 1.0);
				bbMin = glm::min(bbMin, transformedPosition);
				bbMax = glm::max(bbMax, transformedPosition);
			}
		}

		// Add some bading in case the model is a plane
		float padding = 0.5f;
		if (bbMin.x == bbMax.x)
		{
			bbMin.x -= padding;
			bbMax.x += padding;
		}
		else if (bbMin.y == bbMax.y)
		{
			bbMin.y -= padding;
			bbMax.y += padding;
		}
		else if (bbMin.z == bbMax.z)
		{
			bbMin.z -= padding;
			bbMax.z += padding;
		}
	}

	bool Model::checkCollision(const glm::vec3& position) const
	{
		if(!isCollisionChecked)
			return false;

		bool xCollision = (position.x >= bbMin.x && position.x <= bbMax.x);
		bool yCollision = (position.y >= bbMin.y && position.y <= bbMax.y);
		bool zCollision = (position.z >= bbMin.z && position.z <= bbMax.z);

		return xCollision && yCollision && zCollision;
	}

	void Model::render(Program& program)
	{
		program.setMat4("uM_m", getModelMatrix());
		for (Mesh& mesh : meshes)
			mesh.render(program);
	}
}