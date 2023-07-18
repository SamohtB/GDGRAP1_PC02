#include "Perspective.hpp"

using namespace camera;

Perspective::Perspective()
{
	this->FOV = 60.f;
	this->aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
}

void Perspective::SetProjectionMatrix(float FOV)
{
	this->FOV = FOV;
	this->projection_matrix = glm::perspective(glm::radians(this->FOV), aspectRatio, 0.1f, 100.0f);
}
