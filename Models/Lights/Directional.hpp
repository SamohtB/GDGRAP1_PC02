#pragma once
#ifndef LIGHT_DIRECTIONAL_HPP
#define LIGHT_DIRECTIONAL_HPP

#include "../Light.hpp"

using namespace models;

namespace light
{
    class Directional : public Light
    {
    public:
        Directional(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path, glm::vec3 pos,
            glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr, float specStr, float specPhong);
        glm::vec3 GetDirection() { return this->direction; }
        void SetDirection(glm::vec3 direction) { this->direction = direction; }

    private:
        glm::vec3 direction;

    };
}

#endif // !LIGHT_POINT_HPP



