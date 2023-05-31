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
			calculateDeltaTime();

			loopCallback();
			inputCallback(window);

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}

	Window::~Window()
	{
		exit();
	}

	void Window::exit()
	{
		if(window != nullptr)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
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

	void Window::toggleFullScreen()
	{
		static int windowHeight, windowWidth, xPos, yPos;
		bool isFullscreen = glfwGetWindowMonitor(window) != nullptr;
		if (!isFullscreen)
		{
			//Save current h/w
			glfwGetWindowSize(window, &windowWidth, &windowHeight);
			glfwGetWindowPos(window, &xPos, &yPos);

			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			// Get resolution of monitor
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			// Switch to full screen
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(window, nullptr, xPos, yPos, windowWidth, windowHeight, 0);
		}
	}
}