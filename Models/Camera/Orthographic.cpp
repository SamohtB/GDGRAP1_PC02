#include "Orthographic.hpp"

using namespace camera;

Orthographic::Orthographic()
{
	this->projection_matrix = glm::ortho(2.f, -2.f, 2.f, -2.f, -1.f, 1.f); //default
}

void Orthographic::SetProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
{
	this->projection_matrix = glm::ortho(left, right, bottom, top, near, far);
}
