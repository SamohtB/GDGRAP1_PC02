#pragma once
#ifndef CONTROLLER_GAME_OBJECT_MANAGER_HPP
#define CONTROLLER_GAME_OBJECT_MANAGER_HPP

#include "GLFW/glfw3.h"
#include "../../Models/GameObject.hpp"

namespace controller
{
	using namespace models;

	class GameObjectManager
	{
		public:
			void ProcessInput(GLFWwindow* gameWindow);
			void Update(float deltaTime);
			void Draw();

			void AddObject(GameObject* pGameObject);
			void DeleteObject(GameObject* pGameObject);
		
		private:
			GameObjectManager() {}
			GameObjectManager(const GameObjectManager&) = delete;
			GameObjectManager& operator = (const GameObjectManager&) = delete;
			static GameObjectManager* Instance;

		private:
			std::vector<GameObject*> gameObjectList;

		public:
			static GameObjectManager* GetInstance();

	};
}
#endif // !CONTROLLER_GAME_OBJECT_MANAGER_HPP
