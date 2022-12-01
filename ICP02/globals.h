#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

#include <GL/glew.h> 
#include <GL/wglew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "camera.h"


// Global types definition
struct s_globals {
    cv::VideoCapture capture;
    GLFWwindow* window;
    std::string title = "My awsome app";
    int height;
    int width;
	glm::vec4 color;
    Camera* camera = new Camera();
};

struct winModeConfig {
    int height;
    int width;
    int xPos;
    int yPos;
};


// Global variable initialization
inline s_globals globals;
inline winModeConfig winConfig;