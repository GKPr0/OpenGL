#pragma once
#include <glm/glm.hpp>
#include "../base/Program.h"

namespace Engine 
{
	class Renderable {
	public:
		
		virtual void render(Program& program) = 0;

		GLuint getVao() const;

		glm::mat4 getModelMatrix() const;

		void rotate(const float& angle, const glm::vec3& vec);
		void translate(const glm::vec3& translate);
		void scale(const glm::vec3& vec);

	protected:
		GLuint vao;

	private:
		glm::vec3 mPosition = glm::vec3(0.0f);
		glm::vec3 mScale = glm::vec3(1.0f);
		glm::mat4 mRotation = glm::mat4(1.0f);
	};
}