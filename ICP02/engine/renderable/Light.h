#pragma once
#include <glm/glm.hpp>
#include "Renderable.h"
#include "../Settings.h"



namespace Engine 
{
	class Light: public Renderable {
	public:
		void setAmbientColor(const glm::vec3 color) { ambientColor = color; }
		glm::vec3 getAmbientColor() const { return ambientColor; }

		void setDiffuseColor(const glm::vec3 color) { diffuseColor = color; }
		glm::vec3 getDiffuseColor() const { return diffuseColor; }

		void setSpecularColor(const glm::vec3 color) { specularColor = color; }
		glm::vec3 getSpecularColor() const { return specularColor; }
		
		void setConstantAttenuation(const float attenuation) { constantAttenuation = attenuation; }
		float getConstanAttenuation() const { return constantAttenuation; }
		
		void setLinearAttenuation(const float attenuation) { linearAttenuation = attenuation; }
		float getLinearAttenutation() const  { return linearAttenuation; }
		
		void setQuadraticAttenuation(const float attenuation) { quadraticAttenuation = attenuation; }
		float getQuadraticAttenuation() const { return quadraticAttenuation; }

	protected:
		unsigned id;
		glm::vec3 ambientColor;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;

		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;

	};
}
