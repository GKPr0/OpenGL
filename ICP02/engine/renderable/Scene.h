#pragma once
#include "../base/Window.h"
#include "../base/Camera.h"

#include <vector>
#include "Model.h"
#include "../base/ProgramsManager.h"
#include "Light.h"
#include "SkyBox.h"

namespace Engine
{
	class Scene {
	public:
		Scene(Window& window, Camera& camera, ProgramsManager& programs);

		void render();

		void setSkyBox(SkyBox& skyBox) { this->skyBox = &skyBox; }
		void addObject(Model& model) { objects.push_back(&model); }
		void addLight(Light& light) { lights.push_back(&light); }

		const std::vector<Model*>& getObjects() const { return objects; }
		const std::vector<Light*>& getLights() const { return lights; }
		const SkyBox* getSkyBox() const { return skyBox; }

	private:
		Window& window;
		Camera& camera;
		ProgramsManager& programs;

		SkyBox* skyBox;
		std::vector<Model*> objects;
		std::vector<Light*> lights;
		
		void renderSkyBox(Program& program);
		void renderObjects(Program& program);
		void renderLights(Program& program);
	};
}
