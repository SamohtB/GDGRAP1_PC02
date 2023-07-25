#pragma once
#ifndef ENTITY_CENTER_OBJECT_HPP
#define ENTITY_CENTER_OBJECT_HPP

#include "../GameObject.hpp"

#include "../Component/Renderer/Renderer.hpp"
#include "../Component/Transform/Transform.hpp"

namespace entity
{
	using namespace models;
	using namespace components;

	class CenterObject : public GameObject
	{
		public:
			CenterObject(std::string name);

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

		std::unordered_map<int, bool*> keyMap;


	};
}

#endif // !ENTITY_CENTER_OBJECT_HPP

