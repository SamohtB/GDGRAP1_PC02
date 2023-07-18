#include "Point.hpp"

using namespace light;

Point::Point(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path, glm::vec3 pos,
	glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr, float specStr, float specPhong)
	: Light(Mesh_Path, Vert_Path, Frag_Path, Tex_path, pos, lightColor, ambientColor, ambientStr,
		specStr, specPhong) {}

void Point::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix)
{
	glm::mat4 model_matrix = this->GetModelMatrix();

	this->Renderer::Draw(model_matrix, view_matrix, projection_matrix);
}