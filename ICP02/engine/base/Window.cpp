#include "Window.h"
#include "../Engine.h"

#include <fstream>

namespace Engine {

	Window::Window(const unsigned width, const unsigned height, const std::string title) :
		width(width), height(height), title(title)
	{
		initGlfw();

		this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window)
		{
			std::cerr << "GLFW window creation error." << std::endl;
			exit();
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);  //V-sync

		initGlew();

		glViewport(0, 0, width, height);
	}

	void Window::startRender()
	{

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}

	void Window::stopRender()
	{
		glfwSetWindowShouldClose(window, true);
	}


	Window::~Window()
	{
		exit();
	}

	void Window::exit() const
	{
		glfwTerminate();
	}

	void Window::setTitle(const std::string& title)
	{
		this->title = title;
		glfwSetWindowTitle(window, title.c_str());
	}

	void Window::setSize(const unsigned& width, const unsigned& height)
	{
		this->width = width;
		this->height = height;
		glViewport(0, 0, width, height);
	}
}