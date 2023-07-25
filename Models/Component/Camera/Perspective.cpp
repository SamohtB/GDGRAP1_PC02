#include "Perspective.hpp"

using namespace components;

Perspective::Perspective(std::string name) : Camera(name)
{
	SetProjectionMatrix(60.f);
}

void Perspective::SetProjectionMatrix(float FOV)
{
	this->projection_matrix = glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 100.0f);
}

glm::mat4 Perspective::GetProjectionMatrix()
{
	return this->projection_matrix;
}
