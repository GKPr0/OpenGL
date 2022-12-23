#pragma once
#include "Light.h"


namespace Engine 
{
	class SpotLight : public Light {
	public:
		SpotLight(const glm::vec3& position = settings.lightPosition,
					const glm::vec3& direction = glm::vec3(0.0f),
					const glm::vec3& ambientColor = settings.ambientColor,
					const glm::vec3& diffuseColor = settings.diffuseColor,
					const glm::vec3& specularColor = settings.specualrColor,
					const float& constantAttenuation = settings.constantAttenuation,
					const float& linearAttenuation = settings.linearAttenuation,
					const float& quadraticAttenuation = settings.quadraticAttenuation,
					const float& cutOff = settings.cutOff,
					const float& outerCutOff = settings.outerCutOff);

		virtual void render(Program& program) override;
		
		static unsigned count;

		void setDirection(const glm::vec3& direction) { this->direction = direction; }
	private:
		glm::vec3 direction;
		float cutOff;
		float outerCutOff;
	};
}