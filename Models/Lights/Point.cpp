#include "Point.hpp"

using namespace light;

Point::Point(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path, glm::vec3 pos,
	glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr, float specStr, float specPhong)
	: Light(Mesh_Path, Vert_Path, Frag_Path, Tex_path, pos, lightColor, ambientColor, ambientStr,
		specStr, specPhong) 
{
    this->KEY_W = false;
    this->KEY_A = false;
    this->KEY_S = false;
    this->KEY_D = false;
    this->KEY_E = false;
    this->KEY_Q = false;
}

void Point::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::vec3 lightColor)
{
	glm::mat4 model_matrix = this->GetModelMatrix();

	this->Renderer::Draw(model_matrix, view_matrix, projection_matrix, lightColor);
}

void Point::ProcessInput(GLFWwindow* gameWindow)
{
    for (const auto& entry : keyMap)
    {
        int key = entry.first;
        bool* keyStatus = entry.second;
        int status = glfwGetKey(gameWindow, key);
        *keyStatus = (status == GLFW_PRESS);
    }
}

void Point::Update(float tDeltaTime)
{
    float x, y, z;

    if (this->KEY_A)
    {
        
    }

    if (this->KEY_D)
    {
        
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
    float x = radius * sin(angleX) * cos(angleY);
    float y = radius * sin(angleX) * sin(angleY);
    float z = radius * cos(angleX);

    glm::vec3 prevPos = this->GetPosition();

    glm::vec3 newPos = glm::vec3(x + prevPos.x, y + prevPos.y, z + prevPos.z);

    this->SetPosition(newPos);
}