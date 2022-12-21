#pragma once
#include "../base/Window.h"
#include "../base/Camera.h"

#include <vector>
#include "Model.h"
#include "../base/ProgramsManager.h"
#include "Light.h"

namespace Engine
{
	class Scene {
	public:
		Scene(Window& window, Camera& camera, ProgramsManager& programs);

		void render();

		void addObject(Model& model);
		void addLight(Light& light);

		const std::vector<Model*>& getObjects() const;
		const std::vector<Light*>& getLights() const;

	private:
		Window& window;
		Camera& camera;
		ProgramsManager& programs;

		std::vector<Model*> objects;
		std::vector<Light*> lights;

		void initProgram(Program& program);

		void renderObjects(Program& program);
		void renderLights(Program& program);
	};
}
