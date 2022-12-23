#pragma once
#include <glm/glm.hpp>
#include "Renderable.h"
#include "../Settings.h"



namespace Engine 
{
	class Light: public Renderable {
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
