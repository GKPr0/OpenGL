#pragma once
#include "../base/Window.h"
#include "../base/Camera.h"

#include <vector>
#include "Model.h"
#include "../base/ProgramsManager.h"

namespace Engine
{
	class Scene {
	public:
		Scene(Window& window, Camera& camera, ProgramsManager& programs);

		void render();

		void addObject(Model& model);

		const std::vector<Model*>& getObjects() const;

	private:
		Window& window;
		Camera& camera;
		ProgramsManager& programs;

		std::vector<Model*> objects;

		void initProgram(Program& program);

		void renderObjects(Program& program);
	};
}
