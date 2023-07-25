#pragma once
#ifndef MODELS_GAME_OBJECT_HPP
#define MODELS_GAME_OBJECT_HPP

#include "BaseComponents/Renderer/Renderer.hpp"
#include "BaseComponents/Transform/Transform.hpp"
#include <unordered_map>

namespace models {
    using namespace base_component;

    class GameObject : public Transform, public Renderer 
    {
        public:
            GameObject(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path);
            virtual ~GameObject() = default;

        public:
            virtual void ProcessInput(GLFWwindow* window);
            virtual void Update(float tDeltaTime);
            virtual void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix,
                glm::vec3 light_pos, glm::vec3 light_color, float ambient_str, glm::vec3 ambient_color,
                float spec_str, float spec_phong, glm::vec3 camera_pos);

        private:
            bool KEY_W;
            bool KEY_S;
            bool KEY_A;
            bool KEY_D;
            bool KEY_Q;
            bool KEY_E;

            const float rotationSpeed = 100.0f;

            unordered_map<int, bool*> keyMap = {
                {GLFW_KEY_Q, &this->KEY_Q},
                {GLFW_KEY_W, &this->KEY_W},
                {GLFW_KEY_A, &this->KEY_A},
                {GLFW_KEY_S, &this->KEY_S},
                {GLFW_KEY_D, &this->KEY_D},
                {GLFW_KEY_E, &this->KEY_E}
            };
    };
}
#endif
