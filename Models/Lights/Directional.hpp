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

        void ProcessInput(GLFWwindow* gameWindow);
        void Update(float tDeltaTime);

        glm::vec3 GetLightColor(bool isPerspective) override { return this->lightColor; }
        glm::vec3 GetAmbientColor(bool isPerspective) override { return this->ambientColor; }

    private:
        glm::vec3 direction;
        glm::vec3 lightColor;
        glm::vec3 ambientColor;
        const float intensitySpeed = 10.0f;
        bool KEY_LEFT;
        bool KEY_RIGHT;

        unordered_map<int, bool*> keyMap =
        {
            {GLFW_KEY_LEFT, &this->KEY_LEFT},
            {GLFW_KEY_RIGHT, &this->KEY_RIGHT}
        };

    };
}

#endif // !LIGHT_POINT_HPP



