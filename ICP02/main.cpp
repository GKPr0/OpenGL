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

Engine::Window* window;
Engine::Scene* scene;
Engine::Camera* camera;

void loop();
void scrollCallback(GLFWwindow* glfWindow, double xoffset, double yoffset);
void mouseMoveCallback(GLFWwindow* glfWindow, double xpos, double ypos);
void resizeCallback(GLFWwindow* glfWindow, int width, int height);
void inputCallback(GLFWwindow* glfWindow);

int main()
{
	window = new Engine::Window(800, 800);
	window->setTitle("My awsome teapot");
	window->setRenderMethod(loop);
	window->setInputCallback(inputCallback);
	window->setResizeCallback(resizeCallback);
	window->setScrollCallback(scrollCallback);
	window->setMouseMoveCallback(mouseMoveCallback);
	window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	camera = new Engine::Camera(*window,glm::vec3(0.0f,0.0f,50.0f));

	Engine::ProgramsManager programs = Engine::ProgramsManager();
	auto objProg = Engine::Program("resources/shaders/object.vert", "resources/shaders/object.frag"); //Why this dont work if created inside prog manager?
	programs.addProgram("object", objProg);
	auto skyBoxProg = Engine::Program("resources/shaders/skyBox.vert", "resources/shaders/skyBox.frag");
	programs.addProgram("skybox", skyBoxProg);

	Engine::TexturesManager textures = Engine::TexturesManager();
	textures.addTexture("box", "D:/Programming/Cpp/ICP04/ICP02/resources/textures/box_rgb888.png");
	textures.addTexture("fur", "D:/Programming/Cpp/ICP04/ICP02/resources/textures/fur.jpg");
	textures.addTexture("steel", "D:/Programming/Cpp/ICP04/ICP02/resources/textures/steel.jpg");
	
	scene = new Engine::Scene(*window, *camera, programs);

	std::vector<std::string> faces
	{
		"D:/Programming/Cpp/ICP04/ICP02/resources/skybox/right.jpg",
		"D:/Programming/Cpp/ICP04/ICP02/resources/skybox/left.jpg",
		"D:/Programming/Cpp/ICP04/ICP02/resources/skybox/top.jpg",
		"D:/Programming/Cpp/ICP04/ICP02/resources/skybox/bottom.jpg",
		"D:/Programming/Cpp/ICP04/ICP02/resources/skybox/front.jpg",
		"D:/Programming/Cpp/ICP04/ICP02/resources/skybox/back.jpg"
	};
	Engine::SkyBox skyBox = Engine::SkyBox(faces);
	skyBox.scale(glm::vec3(700.0f));
	scene->setSkyBox(skyBox);

	Engine::Light light = Engine::Light(glm::vec3(0.0f, 100.0f, 0.0f));
	scene->addLight(light);

	Engine::Model teapot = Engine::Model("D:/Programming/Cpp/ICP04/ICP02/resources/obj/teapot_tri_vnt.obj", textures.getTexture("steel"));
	scene->addObject(teapot);

	Engine::Model sphere = Engine::Model("D:/Programming/Cpp/ICP04/ICP02/resources/obj/sphere_tri_vnt.obj", textures.getTexture("box"));
	sphere.translate(glm::vec3(20.0f, 0.0f, 20.0f));
	sphere.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	scene->addObject(sphere);

	Engine::Model bunny = Engine::Model("D:/Programming/Cpp/ICP04/ICP02/resources/obj/bunny_tri_vnt.obj", textures.getTexture("fur"));
	bunny.translate(glm::vec3(-20.0f, 0.0f, 20.0f));
	scene->addObject(bunny);

	window->startRender();
}

void loop() 
{
	for (auto object : scene->getObjects())
		object->rotateY(1.0f);

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