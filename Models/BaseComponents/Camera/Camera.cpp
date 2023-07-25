#include "Camera.hpp"

using namespace base_component;

Camera::Camera() : Transform ()
{
	this->SetPosition(glm::vec3(0.f, 0.f, 10.f));
	this->center = glm::vec3(0.f, 0.f, 0.f);

	WORLD_UP = glm::normalize(glm::vec3(0.f, 1.f, 0.f));

	SetViewMatrix();
}

void Camera::MoveCamera(glm::vec3 movement)
{
	this->Move(movement);
	SetViewMatrix();
}

void Camera::SetCameraPos(glm::vec3 new_pos)
{
	this->SetPosition(new_pos);
	SetViewMatrix();
}

void Camera::SetCenter(glm::vec3 orientation)
{
	this->center = (orientation);
	SetViewMatrix();
}

void Camera::SetViewMatrix()
{ 
	this->view_matrix = glm::lookAt(this->GetPosition(), this->center, WORLD_UP);
}
