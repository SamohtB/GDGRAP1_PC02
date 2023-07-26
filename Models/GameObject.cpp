#include "GameObject.hpp"

using namespace models;

GameObject::GameObject(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path) 
    : Renderer (Mesh_Path, Vert_Path, Frag_Path, Tex_path), Transform ()
{
    this->KEY_W = false;
    this->KEY_A = false;
    this->KEY_S = false;
    this->KEY_D = false;
    this->KEY_E = false;
    this->KEY_Q = false;
}

void GameObject::ProcessInput(GLFWwindow* gameWindow) 
{
    for (const auto& entry : keyMap)
    {
        int key = entry.first;
        bool* keyStatus = entry.second;
        int status = glfwGetKey(gameWindow, key);
        *keyStatus = (status == GLFW_PRESS);
    }
}

void GameObject::Update(float tDeltaTime) 
{
    if (this->KEY_A)
    {
        this->Rotate(RotationAxis::YAW, this->rotationSpeed * tDeltaTime * -1);
    }

    if (this->KEY_D)
    {
        this->Rotate(RotationAxis::YAW, this->rotationSpeed * tDeltaTime);
    }

    if (this->KEY_W)
    {
        this->Rotate(RotationAxis::PITCH, this->rotationSpeed * tDeltaTime * -1);
    }
    if (this->KEY_S)
    {
        this->Rotate(RotationAxis::PITCH, this->rotationSpeed * tDeltaTime);
    }
    if (this->KEY_Q)
    {
        this->Rotate(RotationAxis::ROLL, this->rotationSpeed * tDeltaTime);
    }
    if (this->KEY_E)
    {
        this->Rotate(RotationAxis::ROLL, this->rotationSpeed * tDeltaTime * -1);
    }
}

void GameObject::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::vec3 point_light_pos,
    glm::vec3 point_light_color, float point_ambient_str, glm::vec3 point_ambient_color,
    float point_spec_str, float point_spec_phong, float point_intensity, glm::vec3 dir_direction, 
    glm::vec3 dir_light_color, float dir_ambient_str, glm::vec3 dir_ambient_color,
    float dir_spec_str, float dir_spec_phong, float dir_intensity, glm::vec3 camera_pos)
{
    glm::mat4 transform_matrix = this->GetModelMatrix();
    
    this->Renderer::Draw(transform_matrix, view_matrix, projection_matrix, 
        point_light_pos, point_light_color, point_ambient_str, point_ambient_color, point_spec_str, 
        point_spec_phong, point_intensity, 
        dir_direction, dir_light_color, dir_ambient_str, dir_ambient_color, dir_spec_str, 
        dir_spec_phong, dir_intensity, camera_pos);
}

