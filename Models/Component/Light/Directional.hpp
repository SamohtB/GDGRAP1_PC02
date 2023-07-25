#pragma once
#ifndef COMPONENTS_DIRECTIONAL_HPP
#define COMPONENTS_DIRECTIONAL_HPP

#include "Light.hpp"

namespace components
{
    class Directional : public Light
    {
    public:
        Directional(std::string name);
        glm::vec3 GetDirection();
        void SetDirection(glm::vec3 direction);

    private:
        glm::vec3 direction;

    };
}

#endif // !LIGHT_POINT_HPP



