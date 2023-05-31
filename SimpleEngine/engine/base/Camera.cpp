#include "Camera.h"
#include <algorithm>
#include "../Engine.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Engine 
{
	Camera::Camera(Window& window,
		const glm::vec3& position,
		const glm::vec3& diretion,
		const float pitch,
		const float yaw,
		const float speed,
		const float mouseSensitivity,
		const float zoomSensitivity,
		const float fov,
		const float nearPlane,
		const float farPlane) 
		: window(window), position(position), direction(direction), pitch(pitch), yaw(yaw),
		speed(speed), mouseSensitivity(mouseSensitivity), zoomSensitivity(zoomSensitivity),
		fov(fov), nearPlane(nearPlane), farPlane(farPlane)
	{
		update();
	}

	void Camera::update() 
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction = glm::normalize(front);
		right = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
		up = glm::normalize(glm::cross(right, direction));
	}

	void Camera::moveRight()
	{
		position += right * (speed * deltaTime);
	}

	void Camera::moveLeft()
	{
		position -= right * (speed * deltaTime);
	}

	void Camera::moveUp()
	{
		position += direction * (speed * deltaTime);
	}

	void Camera::moveDown()
	{
		position -= direction * (speed * deltaTime);
	}

	void Camera::rotate(const float offsetX, const float offsetY)
	{
		yaw += offsetX * mouseSensitivity;
		pitch += offsetY * mouseSensitivity;
		pitch = std::clamp(pitch, -89.0f, 89.0f);

		update();
	}

	void Camera::zoom(const double direction)
	{
		float newFov = fov + direction * zoomSensitivity;
		fov = std::clamp(newFov, settings.cameraMinZoom, settings.cameraMaxZoom);
		update();
	}

	const glm::mat4 Camera::getProjectionMatrix() const
	{
		return glm::perspective(
			glm::radians(fov),
			(float)window.getWidth() / (float)window.getHeight(),
			nearPlane,
			farPlane
		);
	}

	const glm::mat4 Camera::getViewMatrix() const
	{
		return glm::lookAt(
			position,
		    position + direction,
			up
		);
	}
}