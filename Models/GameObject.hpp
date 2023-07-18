#pragma once
#ifndef MODELS_GAME_OBJECT_HPP
#define MODELS_GAME_OBJECT_HPP

#include "BaseComponents/Renderer/Renderer.hpp"
#include "BaseComponents/Transform/Transform.hpp"

namespace models {
    using namespace base_component;

    class GameObject : public Transform, public Renderer 
    {
        public:
            GameObject(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path);
            virtual ~GameObject() = default;

        public:
            void ProcessInput();
            void Update(GLuint tDeltaTime);
            void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix,
                glm::vec3 light_pos, glm::vec3 light_color, float ambient_str, glm::vec3 ambient_color,
                float spec_str, float spec_phong, glm::vec3 camera_pos);
    };
}
#endif
