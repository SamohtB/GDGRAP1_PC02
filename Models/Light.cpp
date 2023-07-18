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
}
