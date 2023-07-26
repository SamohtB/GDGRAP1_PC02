#include "Directional.hpp"

using namespace light;

Directional::Directional(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path, glm::vec3 pos,
	glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr, float specStr, float specPhong)
	: Light(Mesh_Path, Vert_Path, Frag_Path, Tex_path, pos, lightColor, ambientColor, ambientStr, 
	 specStr, specPhong)
{
	this->direction = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
    this->KEY_LEFT = false;
    this->KEY_RIGHT = false;

    this->lightColor = lightColor;
    this->ambientColor = ambientColor;
}

void Directional::ProcessInput(GLFWwindow* gameWindow)
{
    for (const auto& entry : keyMap)
    {
        int key = entry.first;
        bool* keyStatus = entry.second;
        int status = glfwGetKey(gameWindow, key);
        *keyStatus = (status == GLFW_PRESS);
    }
}

void Directional::Update(float tDeltaTime)
{

    if (KEY_RIGHT)
    {
        this->IncreaseIntensity(this->intensitySpeed * tDeltaTime);
    }

    if (KEY_LEFT)
    {
        this->IncreaseIntensity(this->intensitySpeed * -tDeltaTime);
    }
}

