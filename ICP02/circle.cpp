#include "circle.h"
#include "globals.h"

Circle::Circle(const std::string vertexShader, const std::string fragShader) : Object(vertexShader, fragShader){}

Circle::Circle(glm::vec3 center, float radius, int triangles, const std::string vertexShader, const std::string fragShader) : Object(vertexShader, fragShader)
{
	this->setVao(center, radius, triangles);
}

void Circle::setVao(glm::vec3 center, float radius, int triangles)
{
    std::vector<circleVertex> vertices = {{center}};
    this->indices = {0};

    float step = 2 * 3.14159 / triangles;
    float angle = 0.0f;

    for (int i = 0; i <= triangles; i++)
    {
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        vertices.push_back({ {x, y, 0} });
        this->indices.push_back(i + 1);

        angle += step;
    }

    {
        GLuint VBO, EBO;
        // Generate the VAO and VBO 
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // Bind VAO (set as the current)
        glBindVertexArray(this->vao);
        // Bind the VBO, set type as GL_ARRAY_BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Fill-in data into the VBO
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(circleVertex), vertices.data(), GL_STATIC_DRAW);
        // Bind EBO, set type GL_ELEMENT_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // Fill-in data into the EBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);
        // Set Vertex Attribute to explain OpenGL how to interpret the VBO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(circleVertex), (void*)(0 + offsetof(circleVertex, position)));
        glEnableVertexAttribArray(0);
        // Bind VBO and VAO to 0 to prevent unintended modification 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void Circle::draw()
{
    Object::draw();

    glUniform4fv(glGetUniformLocation(this->shader, "color"), 1, glm::value_ptr(globals.color));
    glDrawElements(GL_TRIANGLE_FAN, this->indices.size(), GL_UNSIGNED_INT, 0);
}

