#include "Light.hpp"

using namespace components;

Light::Light(std::string name) : Component(name, ComponentType::LIGHT)
{
	position = glm::vec3(0.0f);
	lightColor = glm::vec3(0.0f);
	ambientColor = glm::vec3(0.0f);
	ambientStr = 0.0f;
	specStr = 0.0f;
	specPhong = 0.0f;
	intensity = 100.0f;
}

void Light::SetPosition(glm::vec3 position)
{
	this->position = position;
}

void Light::SetLight(glm::vec3 lightColor)
{
	this->lightColor = lightColor;
}

void Light::SetAmbientColor(glm::vec3 ambientColor)
{
	this->ambientColor = ambientColor;
}

void Light::SetAmbientStr(float ambientStr)
{
	this->ambientStr = ambientStr;
}

void Light::SetSpecStr(float specStr)
{
	this->specStr = specStr;
}

void Light::SetSpecPhong(float specPhong)
{
	this->specPhong = specPhong;
}

void Light::SetIntensity(float intensity)
{
	this->intensity = intensity;
}

glm::vec3 Light::GetPosition()
{
	return position;
}

glm::vec3 Light::GetLightColor()
{
	return lightColor;
}

glm::vec3 Light::GetAmbientColor()
{
	return ambientColor;
}

float Light::GetAmbientStr()
{
	return ambientStr;
}

float Light::GetSpecStr()
{
	return specStr;
}

float Light::GetSpecPhong()
{
	return specPhong;
}

float Light::GetIntensity()
{
	return intensity;
}