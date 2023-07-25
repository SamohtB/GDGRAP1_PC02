#pragma once
#ifndef INPUT_ROTATION_HPP
#define INPUT_ROTATION_HPP

#include "../Component.hpp"
#include "../Transform/Transform.hpp"
#include "../../GameObject.hpp"

#include <GLFW/glfw3.h>
#include <unordered_map>
	
namespace input
{
	using namespace components;
	using namespace models;

	class GameObject;

	class RotationInput : public Component
	{
		public:
			RotationInput(std::string name);
			
	};
}
#endif // !INPUT_ROTATION_HPP
