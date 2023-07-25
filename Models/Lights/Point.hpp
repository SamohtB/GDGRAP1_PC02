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

        void ProcessInput(GLFWwindow* gameWindow);
        void Update(float tDeltaTime);
        void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::vec3 lightColor);

    private:
        const float radius = 10.0f;
        const float rotationSpeed = 100.0f;

        bool KEY_W;
        bool KEY_S;
        bool KEY_A;
        bool KEY_D;
        bool KEY_Q;
        bool KEY_E;

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

#endif // !LIGHT_POINT_HPP



