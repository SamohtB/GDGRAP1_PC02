#include "GameObject.hpp"

using namespace models;

GameObject::GameObject(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path) 
    : Renderer (Mesh_Path, Vert_Path, Frag_Path, Tex_path), Transform ()
{

}

void GameObject::ProcessInput() 
{

}

void GameObject::Update(GLuint tDeltaTime) 
{

}

void GameObject::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix,
    glm::vec3 light_pos, glm::vec3 light_color, float ambient_str, glm::vec3 ambient_color,
    float spec_str, float spec_phong, glm::vec3 camera_pos)
{
    glm::mat4 transform_matrix = this->GetModelMatrix();
    
    this->Renderer::Draw(transform_matrix, view_matrix, projection_matrix, light_pos, light_color, 
        ambient_str, ambient_color, camera_pos, spec_str, spec_phong);
}

