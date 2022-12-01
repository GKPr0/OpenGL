#include <iostream>
#include <sstream>

#include <GL/glew.h> 
#include <GL/wglew.h> 

#include <GLFW/glfw3.h>

#include "inits.h"
#include "globals.h"
#include "callbacks.h"



void initGlew()
{
    GLenum glew_ret;
    glew_ret = glewInit();
    if (glew_ret != GLEW_OK)
    {
        std::cerr << "WGLEW failed with error: " << glewGetErrorString(glew_ret) << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "GLEW successfully initialized to version: " << glewGetString(GLEW_VERSION) << std::endl;
    }
	
    // Platform specific. (Change to GLXEW or ELGEW if necessary.)
    glew_ret = wglewInit();
    if (glew_ret != GLEW_OK)
    {
        std::cerr << "WGLEW failed with error: " << glewGetErrorString(glew_ret) << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "WGLEW successfully initialized platform specific functions." << std::endl;
    }

    // enable Z buffer test
    glEnable(GL_DEPTH_TEST);

    // ALL objects are non-transparent, cull back face of polygons 
    glEnable(GL_CULL_FACE);

    if (glfwExtensionSupported("GL_ARB_debug_output"))
    {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugMessageCallback, NULL);
        std::cout << "GL_DEBUG enabled." << std::endl;
    }
}

void initGlfw() {
    glfwSetErrorCallback(errCallback);

    //initialize GLFW library
    int glfw_ret = glfwInit();
    if (!glfw_ret)
    {
        std::cerr << "GLFW init failed." << std::endl;
        finalize(EXIT_FAILURE);
    }

    // Shader based, modern OpenGL (3.3 and higher)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // only new functions
    
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); 
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    globals.window = glfwCreateWindow(800, 600, globals.title.c_str(), NULL, NULL);
    if (!globals.window)
    {
        std::cerr << "GLFW window creation error." << std::endl;
        finalize(EXIT_FAILURE);
    }

    glfwSetKeyCallback(globals.window, keyCallback);
    glfwSetFramebufferSizeCallback(globals.window, frameBufferSizeCallback);
    glfwSetCursorPosCallback(globals.window, cursorPositionCallback);
    glfwSetMouseButtonCallback(globals.window, mouseButtonCallback);
    glfwSetScrollCallback(globals.window, scrollCallback);

    // Get some GLFW info.
    {
        int major, minor, revision;

        glfwGetVersion(&major, &minor, &revision);
        std::cout << "Running GLFW " << major << '.' << minor << '.' << revision << std::endl;
        std::cout << "Compiled against GLFW " << GLFW_VERSION_MAJOR << '.' << GLFW_VERSION_MINOR << '.' << GLFW_VERSION_REVISION << std::endl;
    }

    glfwMakeContextCurrent(globals.window);	// Set current window.
    glfwSwapInterval(1); //V-sync		
}

void initCamera()
{
    globals.capture = cv::VideoCapture(cv::CAP_DSHOW);

    if (!globals.capture.isOpened())
    {
        std::cerr << "no camera" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Camera " <<
            ": width=" << globals.capture.get(cv::CAP_PROP_FRAME_WIDTH) <<
            ", height=" << globals.capture.get(cv::CAP_PROP_FRAME_HEIGHT) <<
            ", FPS=" << globals.capture.get(cv::CAP_PROP_FPS) << std::endl;
    }
}