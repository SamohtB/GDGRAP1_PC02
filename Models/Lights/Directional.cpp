#include "Directional.hpp"

using namespace light;

Directional::Directional(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path, glm::vec3 pos,
	glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr, float specStr, float specPhong)
	: Light(Mesh_Path, Vert_Path, Frag_Path, Tex_path, pos, lightColor, ambientColor, ambientStr, 
	 specStr, specPhong)
{
	this->direction = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
}

