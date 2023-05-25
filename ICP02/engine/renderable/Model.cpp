#include "Model.h"
#include "../support/OBJloader.h"
#include <map>

namespace Engine {
	Model::Model(const std::string& path, Texture* texture)
	{
		load(path, texture);
	}

	void Model::load(const std::string& path, Texture* texture)
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texPositions;
		std::vector<glm::vec3> normals;

		std::vector<GLuint> indices;

		bool status = loadOBJ(path.c_str(), positions, texPositions, normals);
		if (!status)
		{
			std::cerr << "Failed to load obj from: " << path << std::endl;
			exit(EXIT_FAILURE);
		}

		std::vector<MeshVertex> vertices;
		for (unsigned i = 0; i < positions.size(); i++) {
			MeshVertex vertex = MeshVertex{ positions[i], texPositions[i], normals[i] };
			vertices.push_back(vertex);
			indices.push_back(i);
		}

		Mesh mesh = Mesh(vertices, indices, texture);
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

		aabbMin = aabbMax = modelMatrix * glm::vec4(meshes[0].getVertices()[0].position, 1.0);
		for (auto mesh : meshes)
		{
			for (const auto& vertex : mesh.getVertices())
			{
				glm::vec3 transformedPosition = modelMatrix * glm::vec4(vertex.position, 1.0);
				aabbMin = glm::min(aabbMin, transformedPosition);
				aabbMax = glm::max(aabbMax, transformedPosition);
			}
		}
	}

	bool Model::checkCollision(const glm::vec3& position) const
	{
		bool xCollision = (position.x >= aabbMin.x && position.x <= aabbMax.x);
		bool yCollision = (position.y >= aabbMin.y && position.y <= aabbMax.y);
		bool zCollision = (position.z >= aabbMin.z && position.z <= aabbMax.z);

		return xCollision && yCollision && zCollision;
	}

	void Model::render(Program& program)
	{
		program.setMat4("uM_m", getModelMatrix());
		for (Mesh& mesh : meshes)
			mesh.render(program);
	}
}