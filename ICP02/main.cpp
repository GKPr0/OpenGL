#include <GL/glew.h> 
#include <GL/wglew.h> 

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>

#include "engine/base/Window.h"
#include "engine/base/Camera.h"
#include "engine/renderable/Scene.h"
#include "engine/Engine.h"
#include "engine/base/TexturesManager.h"
#include "engine/renderable/SpotLight.h"
#include "engine/renderable/PointLight.h"

Engine::Window* window;
Engine::Scene* scene;
Engine::Camera* camera;
Engine::SpotLight* flashLight;

Engine::PointLight* sunLight;
Engine::Model* sun;

std::vector<Engine::Model*> boxes;

void loop();
void scrollCallback(GLFWwindow* glfWindow, double xoffset, double yoffset);
void keyCallback(GLFWwindow* glfWindow, int key, int scancode, int action, int mods);
void mouseMoveCallback(GLFWwindow* glfWindow, double xpos, double ypos);
void resizeCallback(GLFWwindow* glfWindow, int width, int height);
void inputCallback(GLFWwindow* glfWindow);

void sunOrbitMotion();
void oscilateBoxes();

int main()
{
	window = new Engine::Window(800, 800);
	window->setTitle("My awsome teapot");
	window->setRenderMethod(loop);
	window->setInputCallback(inputCallback);
	window->setResizeCallback(resizeCallback);
	window->setKeyCallback(keyCallback);
	window->setScrollCallback(scrollCallback);
	window->setMouseMoveCallback(mouseMoveCallback);
	window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	camera = new Engine::Camera(*window,glm::vec3(0.0f,0.0f,50.0f));

	Engine::ProgramsManager programs = Engine::ProgramsManager();
	programs.addProgram("object", "resources/shaders/object.vert", "resources/shaders/object.frag");
	programs.addProgram("skybox", "resources/shaders/skyBox.vert", "resources/shaders/skyBox.frag");

	Engine::TexturesManager textures = Engine::TexturesManager();
	textures.addTexture("box", "resources/textures/box_rgb888.png");
	textures.addTexture("fur", "resources/textures/fur.jpg");
	textures.addTexture("steel", "resources/textures/steel.jpg");
	textures.addTexture("diamond_ore", "resources/textures/mc_diamond_ore.png");
	
	scene = new Engine::Scene(*window, *camera, programs);

	
	Engine::SkyBox skyBox = Engine::SkyBox(std::vector<std::string>
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	});
	skyBox.scale(glm::vec3(500.0f));
	scene->setSkyBox(skyBox);

	sunLight = new Engine::PointLight();
	scene->addLight(*sunLight);

	flashLight = new Engine::SpotLight();
	flashLight->setDiffuseColor(glm::vec3(0.1f, 0.5f, 0.5f));
	flashLight->setSpecularColor(glm::vec3(0.4f, 0.8f, 0.8f));
	flashLight->setLinearAttenuation(0.001f);
	flashLight->setQuadraticAttenuation(0.0005f);
	scene->addLight(*flashLight);


	sun = new Engine::Model("D:/Programming/Cpp/ICP04/ICP02/resources/obj/sphere_tri_vnt.obj", textures.getTexture("fur"));
	sun->scale(glm::vec3(5.0f, 5.0f, 5.0f));
	scene->addObject(*sun);

	Engine::Model teapot =  Engine::Model("D:/Programming/Cpp/ICP04/ICP02/resources/obj/teapot_tri_vnt.obj", textures.getTexture("steel"));
	scene->addObject(teapot);

	Engine::Model sphere = Engine::Model("D:/Programming/Cpp/ICP04/ICP02/resources/obj/sphere_tri_vnt.obj", textures.getTexture("box"));
	sphere.translate(glm::vec3(20.0f, 0.0f, 20.0f));
	sphere.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	scene->addObject(sphere);

	Engine::Model bunny = Engine::Model("D:/Programming/Cpp/ICP04/ICP02/resources/obj/bunny_tri_vnt.obj", textures.getTexture("fur"));
	bunny.translate(glm::vec3(-20.0f, 0.0f, 20.0f));
	scene->addObject(bunny);

	std::vector<std::string> boxesTypes{"box", "diamond_ore", "fur", "steel","box", "diamond_ore", "fur", "steel" ,"box", "diamond_ore", "fur", "steel" };
	float x = 0.0f;
	for (int i = 0; i < boxesTypes.size(); i++)
	{
		Engine::Model* box = new Engine::Model("D:/Programming/Cpp/ICP04/ICP02/resources/obj/cube_triangles_normals_tex.obj", textures.getTexture(boxesTypes[i]));
		box->translate(glm::vec3(x, 0.0f, 100.0f));
		box->scale(glm::vec3(15.0f, 15.0f, 15.0f));
		scene->addObject(*box);
		boxes.push_back(box);
		x += 30;
	}
	
	window->startRender();
}

void loop() 
{
	flashLight->setPosition(camera->getPosition());
	flashLight->setDirection(camera->getDirection());

	sunOrbitMotion();
	oscilateBoxes();

	scene->render();
}

void scrollCallback(GLFWwindow* glfWindow, double xoffset, double yoffset)
{
	//std::cout << "Scrolled xoffset: " << xoffset << " yoffset: " << yoffset << std::endl;
	camera->zoom(-1.0 * yoffset);
}

void mouseMoveCallback(GLFWwindow* glfWindow, double xpos, double ypos)
{
	int width = window->getWidth();
	int height = window->getHeight();

	glfwSetCursorPos(glfWindow, width / 2, height / 2);

	float xOffset = Engine::deltaTime * float(width / 2 - xpos);
	float yOffset = Engine::deltaTime * float(height / 2 - ypos);

	camera->rotate(-xOffset, yOffset);
}

void keyCallback(GLFWwindow* glfWindow, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		window->exit();

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		window->toggleFullScreen();

	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		flashLight->toggle();
}

void resizeCallback(GLFWwindow* glfWindow, int width, int height)
{
	window->setSize(width, height);
}

void inputCallback(GLFWwindow* glfWindow)
{
	
	if (glfwGetKey(glfWindow, GLFW_KEY_UP) == GLFW_PRESS ||
		glfwGetKey(glfWindow, GLFW_KEY_W) == GLFW_PRESS) {
		camera->moveUp();
	}

	if (glfwGetKey(glfWindow, GLFW_KEY_DOWN) == GLFW_PRESS ||
		glfwGetKey(glfWindow, GLFW_KEY_S) == GLFW_PRESS) {
		camera->moveDown();
	}

	if (glfwGetKey(glfWindow, GLFW_KEY_RIGHT) == GLFW_PRESS ||
		glfwGetKey(glfWindow, GLFW_KEY_D) == GLFW_PRESS) {
		camera->moveRight();
	}

	if (glfwGetKey(glfWindow, GLFW_KEY_LEFT) == GLFW_PRESS ||
		glfwGetKey(glfWindow, GLFW_KEY_A) == GLFW_PRESS) {
		camera->moveLeft();
	}
}

void sunOrbitMotion()
{
	static float angle;

	angle += 0.5f;
	if (angle > 360)
		angle = 0;
	auto radius = 1000;
	auto x = radius * sin(3.14 * 2 * angle / 360);
	auto z = radius * cos(3.14 * 2 * angle / 360);

	auto positon = glm::vec3(x, z, 0.0f) + camera->getPosition();

	sunLight->setPosition(positon);
	sun->setPosition(positon);
}

void oscilateBoxes()
{
	static float angle;
	const float amplitude = 10;

	float angle_step = 360.0f / (boxes.size() * 250);
	float phase = 0.0f;
	float phase_step = 360.0f / boxes.size();
	for (auto box :boxes)
	{
		angle += angle_step;
		if (angle > 360)
			angle = 0;
	
		auto positon = box->getPosition();
		positon.y = amplitude * sin(3.14 * 2 * (angle + phase) / 360);

		box->setPosition(positon);
		phase += phase_step;
	}
}