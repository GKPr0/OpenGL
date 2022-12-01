#pragma once

#include "object.h"
#include <vector>

struct triangleVertex {
    glm::vec3 position;
    glm::vec3 color;
};

class Triangle : public Object {
    public:
        Triangle(const std::string vertexShader = "resources/triangle.vert",
                 const std::string fragShader = "resources/triangle.frag");
        Triangle(std::vector<triangleVertex> vertices, 
                 const std::string vertexShader = "resources/triangle.vert",
                 const std::string fragShader = "resources/triangle.frag");
		
        void setVao(std::vector<triangleVertex> vertices);
        void draw();
};