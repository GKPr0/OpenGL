#pragma once
#include <glm/glm.hpp>
#include "Renderable.h"
#include "../Settings.h"



namespace Engine 
{
	class Light: public Renderable {
	public:
		Light(const glm::vec3& position = settings.lightPosition,
			  const glm::vec3& ambientColor = settings.ambientColor,
			  const glm::vec3& diffuseColor = settings.diffuseColor,
			  const glm::vec3& specularColor = settings.specualrColor,
		      const float& constantAttenuation = settings.constantAttenuation,
			  const float& linearAttenuation = settings.linearAttenuation,
			  const float& quadraticAttenuation = settings.quadraticAttenuation);

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
