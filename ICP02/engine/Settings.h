#pragma once
#include <iostream>
#include <glm/glm.hpp>

namespace Engine {

    struct Settings {
        // Window
        std::string title = "My awsome app";
        unsigned windowWidth = 600;
        unsigned windowHeight = 600;

        // OpenGl settings
        unsigned majorVersion = 4;
        unsigned minorVersion = 4;

        // Camera settings
        glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
        float cameraPitch = 0;
        float cameraYaw = -90;
        float cameraSpeed = 10;
        float cameraMouseSensitivity = 0.4f;
        float cameraZoomSensitivity = 5;
        float cameraFov = 45;
        float cameraFar = 1000;
        float cameraNear = 0.05;
    };

    inline Settings settings;
}

