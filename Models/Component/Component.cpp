#include "Component.hpp"

using namespace components;

Component::Component(std::string name, ComponentType type)
{
    this->name = name;
    this->type = type;
    this->owner = NULL;
}

Component::~Component() 
{
    this->owner = NULL;
    this->type = ComponentType::NONE;
}

void Component::AttachOwner(GameObject* owner)
{
    this->owner = owner;
}

void Component::DetachOwner()
{
    delete this;
}

GameObject* Component::GetOwner() {
    return this->owner;
}

ComponentType Component::GetType() {
    return this->type;
}

std::string Component::GetName() {
    return this->name;
}

void Component::SetDeltaTime(float deltaTime) 
{
    this->deltaTime = deltaTime;
}