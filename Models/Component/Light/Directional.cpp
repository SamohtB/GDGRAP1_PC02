#include "Directional.hpp"

using namespace components;

Directional::Directional(std::string name) : Light(name)
{
	this->direction = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
}

glm::vec3 Directional::GetDirection()
{
	return this->direction;
}

void Directional::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

