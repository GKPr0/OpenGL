#pragma once
#include "Light.h"

namespace Engine 
{
	class PointLight : public Light {
	public:
		PointLight(const glm::vec3& position = settings.lightPosition,
					const glm::vec3& ambientColor = settings.ambientColor,
					const glm::vec3& diffuseColor = settings.diffuseColor,
					const glm::vec3& specularColor = settings.specualrColor,
					const float& constantAttenuation = settings.constantAttenuation,
					const float& linearAttenuation = settings.linearAttenuation,
					const float& quadraticAttenuation = settings.quadraticAttenuation);

		virtual void render(Program& program) override;
		static unsigned count;
	};
}