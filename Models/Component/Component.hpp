#pragma once
#ifndef COMPONENTS_COMPONENT_HPP
#define COMPONENTS_COMPONENT_HPP

#include "../Enum/EnumComponentType.hpp"

#include <iostream>

namespace models 
{
    class GameObject;
}

namespace components 
{
    using namespace models;

    class Component
    {
        public:
            Component(std::string strName, ComponentType EType);
            virtual ~Component();

            void AttachOwner(GameObject* pOwner);
            void DetachOwner();

            virtual void Perform() = 0;

        protected:
            GameObject* owner;
            ComponentType type;
            std::string name;
            float deltaTime;
            
        public:
            GameObject* GetOwner();
            ComponentType GetType();
            std::string GetName();
            void SetDeltaTime(float deltaTime);
    };
}
#endif
