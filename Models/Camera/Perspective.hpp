#pragma once
#ifndef CAMERA_PERSPECTIVE_HPP
#define CAMERA_PERSPECTIVE_HPP

#include "../BaseComponents/Camera/Camera.hpp"
#include "../../Config/Settings.hpp"

#include "GLFW/glfw3.h"

using namespace base_component;

namespace camera
{
	class Perspective : public Camera
	{
	public:
		Perspective();
		glm::mat4 GetProjectionMatrix() { return this->projection_matrix; }
		void SetProjectionMatrix(float FOV);

		void ProcessInput(GLFWwindow* gameWindow);
		void Update(float tDeltaTime);

		void UpdateCameraPos(float tDeltaTime);

	private:
		glm::mat4 projection_matrix;
		float FOV;
		float aspectRatio;
		bool BUTTON_1;
		bool isPressed;
		double lastMousePosX;
		double lastMousePosY;
		double mousePosX;
		double mousePosY;
		float theta;
		float phi;
		const float sensitivityX = 0.01f;
		const float sensitivityY = 0.01f;
	};
}


#endif

