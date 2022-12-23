#include "Scene.h"

namespace Engine {

	Scene::Scene(Window& window, Camera& camera, ProgramsManager& programs)
		: window(window), camera(camera), programs(programs) {}

	void Scene::render() {
		glViewport(0, 0, window.getWidth(), window.getHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		
		Program* objectProgram = programs.getProgram("object");
		renderLights(*objectProgram);
		renderObjects(*objectProgram);

		Program* skyBoxProgram = programs.getProgram("skybox");
		renderSkyBox(*skyBoxProgram);
	}
	
	void Scene::renderObjects(Program& program)
	{
		if (program.getId() == 0)
			return;

		program.use();
		program.setMat4("uProj_m", camera.getProjectionMatrix());
		program.setMat4("uV_m", camera.getViewMatrix());

		for (Model* model : objects)
			model->render(program);
	}

	void Scene::renderLights(Program& program)
	{
		if (program.getId() == 0)
			return;

		program.use();
		program.setVec3("cameraPos", camera.getPosition());
		for (unsigned i = 0; i < lights.size(); ++i)
		{
			lights[i]->render(program);
		}
	}

	void Scene::renderSkyBox(Program& program)
	{
		if (program.getId() == 0)
			return;

		program.use();
		program.setMat4("uProj_m", camera.getProjectionMatrix());
		program.setMat4("uV_m", glm::mat4(glm::mat3(camera.getViewMatrix())));

		skyBox->render(program);
	}
}