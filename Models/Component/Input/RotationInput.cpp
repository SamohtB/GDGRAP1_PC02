#include "RotationInput.hpp"

using namespace input;

RotationInput::RotationInput(std::string name) : Component(name, ComponentType::INPUT)
{
    this->rotationSpeed = 100.0f;

    this->KEY_W = false;
    this->KEY_S = false;
    this->KEY_A = false;
    this->KEY_D = false;
    this->KEY_Q = false;
    this->KEY_E = false;

    this->keyMap = 
	{
		{GLFW_KEY_Q, &this->KEY_Q},
		{GLFW_KEY_W, &this->KEY_W},
		{GLFW_KEY_A, &this->KEY_A},
		{GLFW_KEY_S, &this->KEY_S},
		{GLFW_KEY_D, &this->KEY_D},
		{GLFW_KEY_E, &this->KEY_E}
	};
}

void RotationInput::ProcessInput(GLFWwindow* gameWindow)
{
    for (const std::pair<int, bool*>& button : keyMap)
    {
        int key = button.first;
        bool* keyStatus = button.second;
        int status = glfwGetKey(gameWindow, key);
        *keyStatus = (status == GLFW_PRESS);
    }
}

void RotationInput::Update(float deltaTime)
{
    std::vector<Component*> components = this->GetOwner()->GetComponents(ComponentType::TRANSFORM);

    if(!components.empty())
    {
        Transform* transform = (Transform*)components[0];
        if (transform != NULL)
        {
            float rot = this->rotationSpeed * deltaTime;

            if (this->KEY_W)
            {
                transform->Rotate(RotationAxis::PITCH, rot * -1);
            }
            if (this->KEY_S)
            {
                transform->Rotate(RotationAxis::PITCH, rot);
            }
            if (this->KEY_A)
            {
                transform->Rotate(RotationAxis::YAW, rot * -1);
            }
            if (this->KEY_D)
            {
                transform->Rotate(RotationAxis::YAW, rot);
            }
            if (this->KEY_Q)
            {
                transform->Rotate(RotationAxis::ROLL, rot);
            }
            if (this->KEY_E)
            {
                transform->Rotate(RotationAxis::ROLL, rot * -1);
            }
        }
        else
        {
            std::cerr << "TRANSFORM NOT FOUND ON " << this->GetName() << std::endl;
        }   
    }
    else
    {
        std::cerr << "NO TRANSFORM COMPONENT ON " << this->GetName() << std::endl;
    } 
}