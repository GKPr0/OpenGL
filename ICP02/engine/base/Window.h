#pragma once

#include <GL/glew.h> 
#include <GL/wglew.h> 
#include <GLFW/glfw3.h>

#include "../Settings.h"

namespace Engine {
    class Window
    {
        GLFWwindow* window = nullptr;
        unsigned width;
        unsigned height;
        std::string title;

        void (*loopCallback)() = nullptr;
        void (*inputCallback)(GLFWwindow*) = nullptr;

    public:
        Window(const unsigned width = settings.windowWidth,
            const unsigned height = settings.windowHeight,
            const std::string title = settings.title);

        virtual ~Window();

        void setRenderMethod(void (*func)()) { loopCallback = func; }
        void startRender();
        void stopRender();
        void exit() const;

        void setTitle(const std::string& title);
        void setSize(const unsigned& width, const unsigned& height);
        void setMode(const int& type, const int& value) { glfwWindowHint(type, value); }
        void setInputMode(const int& type, const int& value) { glfwSetInputMode(window, type, value); }
        void setResizeCallback(void (*func)(GLFWwindow*, int, int)) { glfwSetFramebufferSizeCallback(window, func); }
        void setKeyCallback(void (*func)(GLFWwindow*, int, int, int, int)) { glfwSetKeyCallback(window, func); }
        void setInputCallback(void (*func)(GLFWwindow*)) { inputCallback = func; }
        void setMouseMoveCallback(void (*func)(GLFWwindow*, double, double)) { glfwSetCursorPosCallback(window, func); }
        void setMouseClickCallback(void (*func)(GLFWwindow*, int, int, int)) { glfwSetMouseButtonCallback(window, func); }
        void setScrollCallback(void (*func)(GLFWwindow*, double, double)) { glfwSetScrollCallback(window, func); }

        void toggleFullScreen();

        unsigned getWidth() const { return width; }
        unsigned getHeight() const { return height; }
        std::string getTitle() const { return title; }
        bool isReady() const { return window != nullptr; }
    };
}

