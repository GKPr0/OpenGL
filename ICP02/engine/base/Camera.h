#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"

namespace Engine {

	class Camera {
	public:

		Camera(Window& window,
			const glm::vec3& position = settings.cameraPosition,
			const glm::vec3& diretion = settings.cameraDirection,
			const float pitch = settings.cameraPitch,
			const float yaw = settings.cameraYaw,
			const float speed = settings.cameraSpeed,
			const float mouseSensitivity = settings.cameraMouseSensitivity,
			const float zoomSensitivity = settings.cameraZoomSensitivity,
			const float fov = settings.cameraFov,
			const float nearPlane = settings.cameraNear,
			const float farPlane = settings.cameraFar);
		
		void update();

		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();
		void rotate(const float offsetX, const float offsetY);
		void zoom(const double direction);

		const glm::mat4 getProjectionMatrix() const;
		const glm::mat4 getViewMatrix() const;
		
		void setPosition(const glm::vec3& position) { this->position = position; }
		const glm::vec3 getPosition() const { return position; }
		const glm::vec3 getDirection() const { return direction; }

	private:
		Window& window;

		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 up;
		glm::vec3 right;

		float speed;
		float mouseSensitivity;
		float zoomSensitivity;

		float pitch;
		float yaw;
		float fov;
		float farPlane;
		float nearPlane;
	};
}