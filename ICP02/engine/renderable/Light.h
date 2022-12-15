#pragma once
#include <glm/glm.hpp>
#include "Renderable.h"



namespace Engine 
{
	class Light: public Renderable {
	public:
		Light(const glm::vec3 position = glm::vec3(0.0f),
			  const glm::vec3 ambientColor = glm::vec3(1.0f),
			  const glm::vec3 diffuseColor = glm::vec3(1.0f),
			  const glm::vec3 specularColor = glm::vec3(1.0f),
		      const float& constantAttenuation = 1.0f,
			  const float& linearAttenuation = 0.0f,
			  const float& quadraticAttenuation = 0.0f);

		virtual void render(Program& program) override;

	private:
		glm::vec3 ambientColor;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;

		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
	};
}
