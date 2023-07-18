#include "Camera.hpp"

using namespace base_component;

Camera::Camera() : Transform ()
{
	this->SetPosition(glm::vec3(0.f, 0.f, 10.f));
	this->orientation = glm::vec3(0.f, 0.f, 0.f);

	WORLD_UP = glm::normalize(glm::vec3(0.f, 1.f, 0.f));

	SetViewMatrix();
}

void Camera::MoveCameraWithCenter(glm::vec3 movement)
{
	this->Move(movement);
	this->orientation += movement;
	SetViewMatrix();
}

void Camera::SetCameraWithCenter(glm::vec3 new_pos)
{
	this->SetPosition(new_pos);
	this->orientation = new_pos;
	SetViewMatrix();
}
