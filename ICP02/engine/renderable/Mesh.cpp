#include "Mesh.h"
#include "../support/OBJloader.h"
#include <algorithm>

namespace Engine 
{
	Mesh::Mesh(const std::vector<MeshVertex>& vertices, const std::vector<GLuint> indices, Texture* texture)
		: vertices(vertices), indices(indices), texture(texture)
	{
		GLuint VBO, EBO;
		// Generate the VAO and VBO 
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(vao);

        // Bind the VBO, set type as GL_ARRAY_BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), vertices.data(), GL_STATIC_DRAW);

        // Bind EBO, set type GL_ELEMENT_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);

        // Set Vertex Attribute to explain OpenGL how to interpret the VBO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(offsetof(MeshVertex, position)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(offsetof(MeshVertex, texPosition)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(offsetof(MeshVertex, normal)));
        glEnableVertexAttribArray(2);

        // Bind VBO and VAO to 0 to prevent unintended modification 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

    void Mesh::render(Program& program)
    {
        //Set texture unit
        glActiveTexture(GL_TEXTURE0);
        program.setInt("tex0", 0);

        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
      
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Mesh::camRelatedRender(Program& program, glm::vec3 cameraPos)
    {
        // Calculate the center point and length to the camera
        std::vector<std::pair<float, GLuint>> triangleData;
        for (int i = 0; i < indices.size(); i += 3)
        {
            glm::vec3 p1 = vertices[indices[i]].position;
            glm::vec3 p2 = vertices[indices[i + 1]].position;
            glm::vec3 p3 = vertices[indices[i + 2]].position;

            // Compute the center of the triangle
            glm::vec3 center = (p1 + p2 + p3) / 3.0f;

            // Compute the distance from the camera
            float length = glm::length(center - cameraPos);

            // Store the center point and the index of the first vertex of the triangle
            triangleData.push_back({ length, i });
        }

        // Sort the triangles by distance from the camera
        std::sort(triangleData.begin(), triangleData.end(),
            [](const std::pair<float, GLuint>& a, const std::pair<float, GLuint>& b)
            {
                return a.first > b.first; // draw further triangles first
            });

        //Set texture unit
        glActiveTexture(GL_TEXTURE0);
        program.setInt("tex0", 0);

        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, texture->getId());

        //Draw triangle separately in right order
        for (const auto& data : triangleData)
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(data.second * sizeof(GLuint)));

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Mesh Mesh::load(const std::string& path, Texture* texture)
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

        return Mesh(vertices, indices, texture);
    }
}


