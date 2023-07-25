#include "Orthographic.hpp"

using namespace camera;

Orthographic::Orthographic() : Camera()
{
	SetProjectionMatrix(-15.f, 15.f, -15.f, 15.f, -1.f, 100.f); //default
}

void Orthographic::SetProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
{
	this->projection_matrix = glm::ortho(left, right, bottom, top, near, far);
}
