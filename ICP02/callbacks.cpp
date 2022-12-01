#include <iostream>
#include <glm/glm.hpp>
#include "callbacks.h"
#include "globals.h"



void errCallback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if ((key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D ||
        key == GLFW_KEY_UP || key == GLFW_KEY_DOWN || key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) &&
        action == GLFW_PRESS)
    {
        std::cout << "Move key pressed : " << key << std::endl;
        //globals.camera->move(key);
    }

    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
		globals.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        globals.color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
    {
        globals.color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }

    //Full/win screen switch
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        bool isFullscreen = glfwGetWindowMonitor(globals.window) != nullptr;
        if (!isFullscreen)
        {
            //Save current h/w
            glfwGetWindowSize(globals.window, &winConfig.width, &winConfig.height);
            glfwGetWindowPos(globals.window, &winConfig.xPos, &winConfig.yPos);

            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            // Get resolution of monitor
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            // Switch to full screen
            glfwSetWindowMonitor(globals.window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(globals.window, nullptr, winConfig.xPos, winConfig.yPos,
                winConfig.width, winConfig.height, 0);
        }
    }
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    globals.width = width;
    globals.height = height;

    std::cout << "Frame buffer size: " << width << " x " << height << std::endl;
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "Mouse moved x: " << xpos << " y: " << ypos << std::endl;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    std::cout << "Clicked button: " << button << " action: " << action << std::endl;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "Scrolled xoffset: " << xoffset << " yoffset: " << yoffset << std::endl;
    globals.camera->zoom(-1.0 * yoffset);
}

void finalize(int code)
{
    // Close OpenGL window if opened and terminate GLFW  
    if (globals.window)
        glfwDestroyWindow(globals.window);
    glfwTerminate();
}

void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    auto const src_str = [source]() {
        switch (source)
        {
        case GL_DEBUG_SOURCE_API: return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
        case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
        case GL_DEBUG_SOURCE_OTHER: return "OTHER";
        default: return "Unknown";
        }
    }();

    auto const type_str = [type]() {
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR: return "ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
        case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER: return "MARKER";
        case GL_DEBUG_TYPE_OTHER: return "OTHER";
        default: return "Unknown";
        }
    }();

    auto const severity_str = [severity]() {
        switch (severity) {
        case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
        case GL_DEBUG_SEVERITY_LOW: return "LOW";
        case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
        case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
        default: return "Unknown";
        }
    }();

    std::cout << "[GL CALLBACK]: " <<
        "source = " << src_str <<
        ", type = " << type_str <<
        ", severity = " << severity_str <<
        ", ID = '" << id << '\'' <<
        ", message = '" << message << '\'' << std::endl;
}
