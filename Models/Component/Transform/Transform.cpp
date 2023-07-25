#include "Transform.hpp"

using namespace components;

Transform::Transform(std::string name) : Component(name, ComponentType::TRANSFORM)
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	pitch = 0.f;
	yaw = 0.f;
	roll = 0.f;
	scale = glm::vec3(1.0f);
}

glm::mat4 Transform::GetModelMatrix()
{
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, position);
	model_matrix = glm::rotate(model_matrix, glm::radians(pitch), glm::vec3(1.f, 0.f, 0.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(yaw), glm::vec3(0.f, 1.f, 0.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(roll), glm::vec3(0.f, 0.f, 1.f));
	model_matrix = glm::scale(model_matrix, scale);

	return model_matrix;
}

void Transform::Move(float x, float y, float z)
{
	glm::vec3 move_amt = glm::vec3(x, y, z);
	this->position += move_amt;
}

void Transform::Move(glm::vec3 vector)
{
	this->position += vector;
}

void Transform::SetPosition(float x, float y, float z)
{
	glm::vec3 new_pos = glm::vec3(x, y, z);
	this->position = new_pos;
}

void Transform::SetPosition(glm::vec3 vector)
{
	this->position = vector;
}

void Transform::Rotate(RotationAxis axis, float theta)
{
	switch (axis)
	{
		case RotationAxis::PITCH:
			this->pitch += theta;
			break;
		case RotationAxis::YAW:
			this->yaw += theta;
			break;
		case RotationAxis::ROLL:
			this->roll += theta;
			break;
	}
}

void Transform::SetRotation(RotationAxis axis, float theta)
{
	switch (axis)
	{
		case RotationAxis::PITCH:
			this->pitch = theta;
			break;
		case RotationAxis::YAW:
			this->yaw = theta;
			break;
		case RotationAxis::ROLL:
			this->roll = theta;
			break;
	}
}

void Transform::Scale(float x, float y, float z)
{
	glm::vec3 new_scalar = glm::vec3(x, y, z);
	this->scale += new_scalar;
}

void Transform::Scale(float scalar)
{
	glm::vec3 new_scalar = glm::vec3(scalar, scalar, scalar);
	this->scale += new_scalar;
}

void Transform::SetScale(float x, float y, float z)
{
	glm::vec3 new_scalar = glm::vec3(x, y, z);
	this->scale = new_scalar;
}

void Transform::SetScale(float scalar)
{
	glm::vec3 new_scalar = glm::vec3(scalar, scalar, scalar);
	this->scale = new_scalar;
}

