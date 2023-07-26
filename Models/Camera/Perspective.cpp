#include "Perspective.hpp"
#include <iostream>
using namespace camera;

Perspective::Perspective() : Camera()
{
	this->aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
	this->SetProjectionMatrix(60.f);
	this->BUTTON_1 = false;
	this->isPressed = false;
	this->lastMousePosX = 0.0;
	this->lastMousePosY = 0.0;
	this->mousePosX = 0.0;
	this->mousePosY = 0.0;
	this->theta = 45.5f;
	this->phi = 89.5f;
}

void Perspective::SetProjectionMatrix(float FOV)
{
	this->FOV = FOV;
	this->projection_matrix = glm::perspective(glm::radians(this->FOV), aspectRatio, 0.1f, 100.0f);
}

void Perspective::ProcessInput(GLFWwindow* gameWindow)
{
	this->BUTTON_1 = glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_LEFT);
	glfwGetCursorPos(gameWindow, &this->mousePosX, &this->mousePosY);
	if (this->BUTTON_1 == GLFW_PRESS && !isPressed)
	{
		glfwGetCursorPos(gameWindow, &this->lastMousePosX, &this->lastMousePosY);
		this->isPressed = true;
	}
	else if (this->BUTTON_1 == GLFW_RELEASE)
	{
		this->isPressed = false;
	}
}

void Perspective::Update(float tDeltaTime)
{
	if (this->BUTTON_1 == GLFW_PRESS)
	{
		UpdateCameraPos(tDeltaTime);
	}
}

void camera::Perspective::UpdateCameraPos(float tDeltaTime)
{
	double deltaX = this->lastMousePosX - this->mousePosX;
	double deltaY = this->lastMousePosY - this->mousePosY;
	theta += tDeltaTime * sensitivityX * static_cast<float>(deltaX);
	phi += tDeltaTime * sensitivityX * static_cast<float>(deltaY);

	float x = 10.f * sin(phi) * cos(theta);
	float y = 10.f * cos(phi);
	float z = 10.f * sin(phi) * sin(theta);

	this->SetCameraPos(glm::vec3(x, y, z));
}
