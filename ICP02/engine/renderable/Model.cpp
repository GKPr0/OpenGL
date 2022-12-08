#include "Model.h"
#include "../support/OBJloader.h"

namespace Engine {
	Model::Model(const std::string& path)
	{
		load(path);
	}

	void Model::load(const std::string& path)
	{
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texPositions;
		std::vector<glm::vec3> normals;

		std::vector<GLuint> indices;

		bool status = loadOBJ(path.c_str(), positions, texPositions, normals);
		if (!status)
		{
			std::cerr << "Failed to load obj from: " << path << std::endl;
			return; // TODO Throw error or clsoe app;
		}

		std::vector<MeshVertex> vertices;
		for (unsigned i = 0; i < positions.size(); i++) {
			MeshVertex vertex = MeshVertex{ positions[i], texPositions[i], normals[i] };
			vertices.push_back(vertex);
			indices.push_back(i);
		}

		Mesh mesh = Mesh(vertices, indices);
		meshes.push_back(mesh);
	}

	void Model::render(Program& program)
	{
		program.setMat4("uM_m", getModelMatrix());
		for (Mesh& mesh : meshes)
			mesh.render(program);
	}
}