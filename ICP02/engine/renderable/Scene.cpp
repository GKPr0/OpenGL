#include "Scene.h"

namespace Engine {

	Scene::Scene(Window& window, Camera& camera, ProgramsManager& programs)
		: window(window), camera(camera), programs(programs) {}

	void Scene::render() {
		glViewport(0, 0, window.getWidth(), window.getHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		Program objectProgram = programs.getObjectProgram();
		renderLights();
		renderObjects(objectProgram);
	}

	void Scene::renderObjects(Program& program)
	{
		initProgram(program);

		for (Model* model : objects)
			model->render(program);
	}

	void Scene::renderLights()
	{
		Program objProgram = programs.getObjectProgram();

		if (objProgram.getId() == 0)
			return;

		for (unsigned i = 0; i < lights.size(); ++i)
		{
			objProgram.use();
			lights[i]->render(objProgram);
		}
	}

	void Scene::initProgram(Program& program)
	{
		if (program.getId() == 0)
			return;

		program.use();
		program.setMat4("uProj_m", camera.getProjectionMatrix());
		program.setMat4("uV_m", camera.getViewMatrix());
	}

	void Scene::addObject(Model& model)
	{
		objects.push_back(&model);
	}

	void Scene::addLight(Light& light)
	{
		lights.push_back(&light);
	}

	const std::vector<Model*>& Scene::getObjects() const
	{
		return objects;
	}

	const std::vector<Light*>& Scene::getLights() const
	{
		return lights;
	}
}