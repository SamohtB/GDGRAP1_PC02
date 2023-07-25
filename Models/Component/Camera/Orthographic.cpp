#include "Orthographic.hpp"

using namespace components;

Orthographic::Orthographic(std::string name) : Camera(name)
{
	SetProjectionMatrix(-15.f, 15.f, -15.f, 15.f, -1.f, 100.f); //default
}

void Orthographic::SetProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
{
	this->projection_matrix = glm::ortho(left, right, bottom, top, near, far);
}

glm::mat4 Orthographic::GetProjectionMatrix()
{
	return this->projection_matrix;
}
