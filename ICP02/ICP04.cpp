#include <GL/glew.h> 
#include <GL/wglew.h> 

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>

//C++
#include <iostream>
#include <thread>


#include "globals.h"
#include "inits.h"
#include "utils.h"
#include "shaders.h"
#include "camera.h"
#include "triangle.h"
#include "circle.h"


int main()
{
    initGlfw();
    initGlew();

    glEnable(GL_CULL_FACE);

    glfwGetWindowSize(glfwGetCurrentContext(), &winConfig.width, &winConfig.height);
    glViewport(0, 0, winConfig.width, winConfig.height);

    Camera* camera = globals.camera;

    std::vector<Object*> objects;

    Triangle* triangle = new Triangle({
            { {-0.5f, -0.5f, 0.0f}, {1.0f,0.0f,0.0f} },
            { {0.5f, -0.5f, 0.0f}, {0.0f,1.0f,0.0f} },
            { {0.0f, 0.5f, 0.0f}, {0.0f,0.0f,1.0f} },
        });
    triangle->setModelMatrix(glm::scale(triangle->getModelMatrix(), glm::vec3(5.0)));
    objects.push_back(triangle);

    int count = 10;
    float step = 2 * 3.14159 / count;
    float angle = 0;
    float radius = 10;
    for (int i = 0; i < 10; i++)
    {
        Circle* circle = new Circle({ 0.0f, 0.0f, 1.0f }, 0.4f, 100);
		
        auto modelMatrix = circle->getModelMatrix();
        modelMatrix = glm::translate(modelMatrix, glm::vec3(radius * cos(angle), -1.0f , radius * sin(angle)));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		circle->setModelMatrix(modelMatrix);

        objects.push_back(circle);

        angle += step;
    }
   
   

    while (!glfwWindowShouldClose(globals.window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->update();

        for (auto object : objects)
            object->draw();
	
        showFPSInTitle();
		
        glfwSwapBuffers(globals.window);
        glfwPollEvents();
    }

    finalize(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}