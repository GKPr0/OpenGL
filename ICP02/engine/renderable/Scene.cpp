#include "Scene.h"
#include <algorithm>

namespace Engine {

	Scene::Scene(Window& window, Camera& camera, ProgramsManager& programs)
		: window(window), camera(camera), programs(programs) {}

	void Scene::render() {
		glViewport(0, 0, window.getWidth(), window.getHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		
		Program* skyBoxProgram = programs.getProgram("skybox");
		renderSkyBox(*skyBoxProgram);

		Program* objectProgram = programs.getProgram("object");
		renderLights(*objectProgram);
		renderObjects(*objectProgram);

		Program* particleProgram = programs.getProgram("particle");
		renderParticles(*particleProgram);

		renderTransparentObjects(*objectProgram);
	}
	
	void Scene::renderObjects(Program& program)
	{
		if (program.getId() == 0)
			return;

		program.use();
		program.setMat4("uProj_m", camera.getProjectionMatrix());
		program.setMat4("uV_m", camera.getViewMatrix());

		for (Model* model : objects)
			if(!model->getTexture()->IsTransparent())
				model->render(program);
	}

	void Scene::renderTransparentObjects(Program& program)
	{
		if (program.getId() == 0)
			return;

		program.use();
		program.setMat4("uProj_m", camera.getProjectionMatrix());
		program.setMat4("uV_m", camera.getViewMatrix());

		glEnable(GL_BLEND); // enable blending
		glDisable(GL_CULL_FACE); // no polygon removal

		// Sort model by distance from camera
		std::vector<std::pair<float, Model*>> modelsWithDistance;
		for (Model* model : objects)
		{
			if (!model->getTexture()->IsTransparent())
				continue;

			float distance = glm::length(camera.getPosition() - model->getPosition());
			modelsWithDistance.push_back(std::make_pair(distance, model));
		}

		std::sort(modelsWithDistance.begin(), modelsWithDistance.end(), [](std::pair<float, Model*> a, std::pair<float, Model*> b) {
			return a.first > b.first; // øazení sestupnì
			});

		for (auto it = modelsWithDistance.begin(); it != modelsWithDistance.end(); ++it)
			it->second->render(program);

		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
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
		if (program.getId() == 0 || skyBox == NULL)
			return;

		program.use();
		program.setMat4("uProj_m", camera.getProjectionMatrix());
		program.setMat4("uV_m", glm::mat4(glm::mat3(camera.getViewMatrix())));

		skyBox->render(program);
	}

	void Scene::renderParticles(Program& program)
	{
		if (program.getId() == 0)
			return;

		program.use();
		program.setMat4("uProj_m", camera.getProjectionMatrix());
		program.setMat4("uV_m", camera.getViewMatrix());

		glEnable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); 	// use additive blending to give it a 'glow' effect

		for (ParticleGenerator* particleGenerator : particleGenerators)
			particleGenerator->render(program);

		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 	// reset to default blending mode
	}
}