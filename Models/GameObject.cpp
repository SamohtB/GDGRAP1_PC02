#include "GameObject.hpp"

using namespace models;

GameObject::GameObject(std::string name)
{
    this->name = name;
}

void GameObject::ProcessInput(GLFWwindow* gameWindow) 
{
    std::vector<Component*> inputComponents = GetComponents(ComponentType::INPUT);

    for (Component* component : inputComponents)
    {
        component->Perform();
    }
}

void GameObject::Update(float deltaTime) 
{
    std::vector<Component*> scriptComponents = GetComponents(ComponentType::SCRIPT);

    for (Component* component : scriptComponents)
    {
        component->SetDeltaTime(deltaTime);
        component->Perform();
    }
}

void GameObject::Draw()
{
    std::vector<Component*> renderComponents = GetComponents(ComponentType::MESH);

    for (Component* component : renderComponents)
    {
        component->Perform();
    }
}

void GameObject::AttachComponent(Component* component) 
{
    this->componentList.push_back(component);
    component->AttachOwner(this);
}

void GameObject::DetachComponent(Component* component) 
{
    int nIndex = -1;
    for (int i = 0; i < this->componentList.size() && nIndex == -1; i++) 
    {
        if (this->componentList[i] == component)
        {
            nIndex = i;
        }
    }

    if (nIndex != -1) {
        this->componentList[nIndex]->DetachOwner();
        this->componentList.erase(this->componentList.begin() + nIndex);
    }
}

std::vector<Component*> GameObject::GetComponents(ComponentType type) 
{
    std::vector<Component*> vecFound = {};

    for (Component* pComponent : this->componentList) 
    {
        if (pComponent->GetType() == type)
        {
            vecFound.push_back(pComponent);
        }
    }

    return vecFound;
}

std::string GameObject::GetName() 
{
    return this->name;
}

