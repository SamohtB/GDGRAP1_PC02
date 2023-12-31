#pragma once
#ifndef CONTROLLER_GAME_HPP
#define CONTROLLER_GAME_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <cmath>

#include "../Config/Settings.hpp"
#include "../Models/GameObject.hpp"
#include "../Models/Lights/Directional.hpp"
#include "../Models/Lights/Point.hpp"
#include "../Models/Camera/Orthographic.hpp"
#include "../Models/Camera/Perspective.hpp"

using namespace models;
using namespace light;
using namespace camera;

namespace Controller
{
	class Game
	{
	public:
		Game();
		void Run();
		

	private:
		void CreateLights();
		void Initialize();
		void ProcessInput();
		void Update(float tDeltaTime);
		void Render();

	private:
		GLFWwindow* gameWindow;
		
		Perspective* perpectiveCamera;
		Orthographic* orthographicCamera;
		Directional* directionalLight;
		Point* pointLight;
		GameObject* centerObject;

		bool isPerspective;
		bool isSpacePressed;
		bool isCenter;
	};
}


#endif // !SYSTEM_GAME_H



