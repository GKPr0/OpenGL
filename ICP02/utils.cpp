#include "utils.h"
#include "globals.h"

#include <fstream>

void showFPSInTitle()
{
    static double lastTime;
    static int nbFrames;

    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    nbFrames++;

    if (delta >= 1.0) {
        double fps = double(nbFrames) / delta;

        std::stringstream ss;
        ss << globals.title << " [" << fps << " FPS]";

        glfwSetWindowTitle(globals.window, ss.str().c_str());

        nbFrames = 0;
        lastTime = currentTime;
    }
}

std::string textFileRead(const std::string fn) {
    std::ifstream file;
    std::stringstream ss;

    file.open(fn);
    if(file.is_open())
    {
        ss << file.rdbuf();
    }
    else
    {
        std::cerr << "Error opening file: " << fn << std::endl;
        exit(EXIT_FAILURE);
    }
      
    return std::move(ss.str());
}
