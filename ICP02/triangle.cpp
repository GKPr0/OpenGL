#include "triangle.h"
#include "globals.h"


Triangle::Triangle(const std::string vertexShader, const std::string fragShader) : Object(vertexShader, fragShader) {}

Triangle::Triangle(std::vector<triangleVertex> vertices, const std::string vertexShader, const std::string fragShader) : Object(vertexShader, fragShader) 
{
    this->setVao(vertices);
}


void Triangle::setVao(std::vector<triangleVertex> vertices)
{
    std::vector<GLuint> indices = { 0, 1, 2 };

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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(triangleVertex), vertices.data(), GL_STATIC_DRAW);
    // Bind EBO, set type GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Fill-in data into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    // Set Vertex Attribute to explain OpenGL how to interpret the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(triangleVertex), (void*)(0 + offsetof(triangleVertex, position)));
    glEnableVertexAttribArray(0);
    // Set end enable Vertex Attribute 1 = Texture Coordinates
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(triangleVertex), (void*)(0 + offsetof(triangleVertex, color)));
    glEnableVertexAttribArray(1);
    // Bind VBO and VAO to 0 to prevent unintended modification 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Triangle::draw()
{
    Object::draw();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}