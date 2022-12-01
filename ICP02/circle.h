#pragma once

#include "object.h"
#include <vector>

struct circleVertex {
	glm::vec3 position;
};

#

class Circle : public Object {
	public:
		Circle(const std::string vertexShader = "resources/circle.vert" ,
			   const std::string fragShader = "resources/circle.frag");
		Circle(glm::vec3 center,
			   float radius,
			   int triangles,
			   const std::string vertexShader = "resources/circle.vert",
			   const std::string fragShader = "resources/circle.frag");

		void setVao(glm::vec3 center, float radius, int triangles);
		void draw();

	private:
		std::vector<GLuint> indices;
};
