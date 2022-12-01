#pragma once

#include <GL/glew.h> 
#include <GL/wglew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera {
	public:
		const glm::mat4 getProjectionMatrix();
		const glm::mat4 getViewMatrix();

		void move(int key);
		void move();
		void zoom(double direction);
		void update();

	private:
		const float moveSpeed = 3.0f;
		const float mouseSpeed = 0.005f;
		const float zoomSpeed = 5.0f;

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

		glm::vec3 position = glm::vec3(0, 0, 5);

		glm::vec3 right;
		glm::vec3 up;
		glm::vec3 direction;

		float horizontalAngle = 3.14f;
		float verticalAngle = 0.0f;
		float fov = 45.0f;

		double lastTime;
		float deltaTime;
};
