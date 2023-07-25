#include "Camera.hpp"

using namespace components;

Camera::Camera(std::string name) : Component(name, ComponentType::CAMERA)
{
	SetViewMatrix();
}

void Camera::SetPosition(glm::vec3 position)
{
	this->position = position;
	SetViewMatrix();
}

void Camera::SetCenter(glm::vec3 center)
{
	this->center = center;
	SetViewMatrix();
}

void Camera::SetPositionAndCenter(glm::vec3 position, glm::vec3 center)
{
	this->position = position;
	this->center = center;
	
	SetViewMatrix();
}

void Camera::MovePositionAndCenter(glm::vec3 position, glm::vec3 center)
{
	this->position += position;
	this->center += center;

	SetViewMatrix();
}

glm::mat4 Camera::GetViewMatrix()
{
	return this->view_matrix;
}

void Camera::SetViewMatrix()
{ 
	this->view_matrix = glm::lookAt(this->position, this->center, WORLD_UP);
}
