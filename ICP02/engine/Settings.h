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
        glm::vec3 cameraPosition = glm::vec3(0.0f);
        glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
        float cameraPitch = 0;
        float cameraYaw = -90;
        float cameraSpeed = 50;
        float cameraMouseSensitivity = 0.6f;
        float cameraZoomSensitivity = 5;
        float cameraMinZoom = 30.0f;
        float cameraMaxZoom = 120.0f;
        float cameraFov = 45;
        float cameraFar = 1000;
        float cameraNear = 0.05;

        // Light settings
        glm::vec3 lightPosition = glm::vec3(0.0f);
        glm::vec3 ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);
        glm::vec3 diffuseColor = glm::vec3(0.1f, 0.1f, 0.1f);
        glm::vec3 specualrColor = glm::vec3(1.0f);
        float constantAttenuation = 1.0f;
        float linearAttenuation = 0.0015f;
        float quadraticAttenuation = 0.0f;
        float cutOff = glm::cos(glm::radians(12.5f));
        float outerCutOff = glm::cos(glm::radians(15.0f));
    };

    inline Settings settings;
}

