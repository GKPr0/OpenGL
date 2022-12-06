#pragma once
#include <iostream>
#include <glm/glm.hpp>

namespace Engine {

    struct Settings {
        std::string title = "Terrain Generator";
        unsigned majorVersion = 4;
        unsigned minorVersion = 1;
        unsigned windowWidth = 1920;
        unsigned windowHeight = 1080;

        float cameraPitch = 0;
        float cameraYaw = -90;
        float cameraSpeed = 7;
        float cameraSensitivity = 0.1;
        float cameraFov = 45;
        float cameraFar = 1000;
        float cameraNear = 0.05;


        glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    };

    inline Settings settings;
}

