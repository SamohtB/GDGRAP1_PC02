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
    this->KEY_UP = false;
    this->KEY_DOWN = false;
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

void Point::ProcessInput2(GLFWwindow* gameWindow)
{
    for (const auto& entry : keyMap2)
    {
        int key = entry.first;
        bool* keyStatus = entry.second;
        int status = glfwGetKey(gameWindow, key);
        *keyStatus = (status == GLFW_PRESS);
    }
}

void Point::Update(float tDeltaTime)
{
    if (KEY_W)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), tDeltaTime * orbitSpeed, glm::vec3(1.0f, 0.0f, 0.0f));
        this->SetPosition(glm::vec3(rotation * glm::vec4(this->GetPosition(), 1.0f)));
    }

    if (KEY_S)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -tDeltaTime * orbitSpeed, glm::vec3(1.0f, 0.0f, 0.0f));
        this->SetPosition(glm::vec3(rotation * glm::vec4(this->GetPosition(), 1.0f)));
    }

    if (KEY_A)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), tDeltaTime * orbitSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
        this->SetPosition(glm::vec3(rotation * glm::vec4(this->GetPosition(), 1.0f)));
    }

    if (KEY_D)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -tDeltaTime * orbitSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
        this->SetPosition(glm::vec3(rotation * glm::vec4(this->GetPosition(), 1.0f)));
    }

    if (KEY_Q)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), tDeltaTime * orbitSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
        this->SetPosition(glm::vec3(rotation * glm::vec4(this->GetPosition(), 1.0f)));
    }

    if (KEY_E)
    {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -tDeltaTime * orbitSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
        this->SetPosition(glm::vec3(rotation * glm::vec4(this->GetPosition(), 1.0f)));
    }

    if (KEY_UP)
    {
        this->IncreaseIntensity(this->intensitySpeed * tDeltaTime);
    }

    if (KEY_DOWN)
    {
        this->IncreaseIntensity(this->intensitySpeed * -tDeltaTime);
    }
}