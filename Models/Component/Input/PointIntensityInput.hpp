#pragma once
#ifndef INPUT_POINT_INTENSITY_HPP
#define INPUT_POINT_INTENSITY_HPP

#include "../Component.hpp"
#include "../Light/Light.hpp"
#include "../../GameObject.hpp"

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace input
{
	using namespace components;
	using namespace models;

	class PointIntensityInput : public Component
	{
	public:
		PointIntensityInput(std::string name); 
		void ProcessInput(GLFWwindow* gameWindow);
		void Update(float deltaTime);

	private:
		float rotationSpeed;

		bool KEY_W;
		bool KEY_S;
		bool KEY_A;
		bool KEY_D;
		bool KEY_Q;
		bool KEY_E;

	};
}

#endif // !INPUT_POINT_INTENSITY_HPP




