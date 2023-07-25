#pragma once
#ifndef MODELS_GAME_OBJECT_HPP
#define MODELS_GAME_OBJECT_HPP

#include "Component/Component.hpp"
#include "Enum/EnumComponentType.hpp"

#include "GLFW/glfw3.h"
#include <unordered_map>

namespace models 
{
    using namespace components;

    class GameObject
    {
        public:
            GameObject(std::string name);
            virtual ~GameObject() = default;

        public:
            virtual void Initialize() = 0;
            virtual void ProcessInput(GLFWwindow* window);
            virtual void Update(float deltaTime);
            virtual void Draw();

            void AttachComponent(Component* component);
            void DetachComponent(Component* component);
            std::vector<Component*> GetComponents(ComponentType type);

            std::string GetName();

        private:
            std::string name;
            std::vector<Component*> componentList;
    };
}
#endif
