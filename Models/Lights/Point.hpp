#pragma once
#ifndef LIGHT_POINT_HPP
#define LIGHT_POINT_HPP

#include "../Light.hpp"

using namespace models;

namespace light
{
    class Point : public Light
    {
    public:
        Point(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path, glm::vec3 pos,
            glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr, float specStr, float specPhong);

        void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix);

    };
}

#endif // !LIGHT_POINT_HPP



