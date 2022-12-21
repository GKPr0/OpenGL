#include "Mesh.h"

namespace Engine 
{
	Mesh::Mesh(const std::vector<MeshVertex>& vertices, const std::vector<GLuint> indices, const Texture& texture)
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

        //TODO Udìlat shader co pùjde napojit
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
        glActiveTexture(GL_TEXTURE0);
        program.setInt("tex0", 0);

        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, texture.getId());
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


