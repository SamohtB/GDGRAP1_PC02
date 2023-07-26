#include "Light.hpp"

using namespace models;

Light::Light(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path, glm::vec3 pos, 
	glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr, float specStr, float specPhong) 
	: GameObject(Mesh_Path, Vert_Path, Frag_Path, Tex_path)
{
	this->SetPosition(pos);
	this->lightColor = lightColor;
	this->ambientColor = ambientColor;
	this->ambientStr = ambientStr;
	this->specStr = specStr;
	this->specPhong = specPhong;
	this->intensity = 1.0f;
}

glm::vec3 Light::GetLightColor(bool isCenter)
{
	if (isCenter)
	{
		lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	}
	else
	{
		lightColor = glm::vec3(1.0f, 0.4f, 0.8f);
	}

	return lightColor;
}

glm::vec3 Light::GetAmbientColor(bool isCenter)
{
	if (isCenter)
	{
		ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
	}
	else
	{
		ambientColor = glm::vec3(1.0f, 0.4f, 0.8f);
	}

	return ambientColor;
}