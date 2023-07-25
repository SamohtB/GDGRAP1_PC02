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

void GameObject::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix,
    glm::vec3 light_pos, glm::vec3 light_color, float ambient_str, glm::vec3 ambient_color,
    float spec_str, float spec_phong, glm::vec3 camera_pos)
{
    glm::mat4 transform_matrix = this->GetModelMatrix();
    
    this->Renderer::Draw(transform_matrix, view_matrix, projection_matrix, light_pos, light_color, 
        ambient_str, ambient_color, camera_pos, spec_str, spec_phong);
}

