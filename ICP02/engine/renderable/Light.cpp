#include "Light.h"

namespace Engine 
{
	Light::Light(const glm::vec3 position, const glm::vec3 ambientColor, const glm::vec3 diffuseColor, const glm::vec3 specularColor,
				const float& constantAttenuation, const float& linearAttenuation, const float& quadraticAttenuation)
	{
		this->mPosition = position;
		this->ambientColor = ambientColor;
		this->diffuseColor = diffuseColor;
		this->specularColor = specularColor;
		this->constantAttenuation = constantAttenuation;
		this->linearAttenuation = linearAttenuation;
		this->quadraticAttenuation = quadraticAttenuation;
	}

	void Light::render(Program& program)
	{
		program.setVec3("lightPosition", mPosition);
		program.setVec3("ambientColor", ambientColor);
		program.setVec3("diffuseColor", diffuseColor);
		program.setVec3("specularColor", specularColor);
		program.setFloat("constantAttenuation", constantAttenuation);
		program.setFloat("linearAttenuation", linearAttenuation);
		program.setFloat("quadraticAttenuation", quadraticAttenuation);
	}
}