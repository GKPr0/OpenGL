#include "camera.h"
#include "globals.h"


const glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}

const glm::mat4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

void Camera::update()
{
	double xpos, ypos;
	glfwGetCursorPos(globals.window, &xpos, &ypos);
	// Reset mouse position for next frame
	glfwSetCursorPos(globals.window, winConfig.width / 2, winConfig.height / 2);

	double currentTime = glfwGetTime();
	this->deltaTime = float(currentTime - lastTime);
	this->lastTime = currentTime;

	// Compute new orientation
	this->horizontalAngle += mouseSpeed * deltaTime * float(winConfig.width / 2 - xpos);
	this->verticalAngle += mouseSpeed * deltaTime * float(winConfig.height / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	this->direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);


	this->right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector : perpendicular to both direction and right
	this->up = glm::cross(right, direction);

	move();

	float ratio = static_cast<float>(winConfig.width) / winConfig.height;
	
	this->projectionMatrix = glm::perspective(
		glm::radians(this->fov), // The vertical Field of View, in radians
		ratio,			            // Aspect Ratio
		0.1f,                           // Near clipping plane
		20000.0f                        // Far clipping plane
	);
	
	this->viewMatrix = glm::lookAt(
		this->position,				
		this->position + this->direction,
		this->up						
	);
}

void Camera::move()
{
	if (glfwGetKey(globals.window, GLFW_KEY_UP) == GLFW_PRESS ||
		glfwGetKey(globals.window, GLFW_KEY_W) == GLFW_PRESS) {
		position += this->direction * this->deltaTime * this->moveSpeed;
	}

	if (glfwGetKey(globals.window, GLFW_KEY_DOWN) == GLFW_PRESS ||
		glfwGetKey(globals.window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= this->direction * this->deltaTime * this->moveSpeed;
	}

	if (glfwGetKey(globals.window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
		glfwGetKey(globals.window, GLFW_KEY_D) == GLFW_PRESS) {
		position += this->right * this->deltaTime * this->moveSpeed;
	}

	if (glfwGetKey(globals.window, GLFW_KEY_LEFT) == GLFW_PRESS ||
		glfwGetKey(globals.window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= this->right * this->deltaTime * this->moveSpeed;
	}
}

void Camera::move(int key)
{
	if (key == GLFW_KEY_W || key == GLFW_KEY_UP)
		position.z -= this->moveSpeed;
	else if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN)
		position.z += this->moveSpeed;
	else if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT)
		position.x += this->moveSpeed;
	else if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT)
		position.x -= this->moveSpeed;
}

void Camera::zoom(double direction)
{
	float newFov = fov + direction * this->zoomSpeed;
	if(newFov < 20)
		newFov = 20;
	else if (newFov > 120)
		newFov = 120;
	
	this->fov = newFov;
}