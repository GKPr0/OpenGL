#include "SpotLight.h"
#include <iostream>  
#include <string>  


namespace Engine
{
	unsigned SpotLight::count = 0;

	SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor,
		const float& constantAttenuation, const float& linearAttenuation, const float& quadraticAttenuation, const float& cutOff, const float& outerCutOff)
	{
		id = count++;
		this->mPosition = position;
		this->direction = direction;
		this->ambientColor = ambientColor;
		this->diffuseColor = diffuseColor;
		this->specularColor = specularColor;
		this->constantAttenuation = constantAttenuation;
		this->linearAttenuation = linearAttenuation;
		this->quadraticAttenuation = quadraticAttenuation;
		this->cutOff = cutOff;
		this->outerCutOff = outerCutOff;
	}

	void SpotLight::render(Program& program)
	{
		std::string light = "spotLights[" + std::to_string(id) + "]";

		program.setVec3(std::string(light + ".position").c_str(), mPosition);
		program.setVec3(std::string(light + ".direction").c_str(), direction);
		program.setVec3(std::string(light + ".ambientColor").c_str(), ambientColor);
		program.setVec3(std::string(light + ".diffuseColor").c_str(), diffuseColor);
		program.setVec3(std::string(light + ".specularColor").c_str(), specularColor);
		program.setFloat(std::string(light + ".constantAttenuation").c_str(), constantAttenuation);
		program.setFloat(std::string(light + ".linearAttenuation").c_str(), linearAttenuation);
		program.setFloat(std::string(light + ".quadraticAttenuation").c_str(), quadraticAttenuation);
		program.setFloat(std::string(light + ".cutOff").c_str(), cutOff);
		program.setFloat(std::string(light + ".outerCutOff").c_str(), outerCutOff);
	}
}