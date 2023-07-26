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

	private:
		glm::mat4 projection_matrix;
		float FOV;
		float aspectRatio;
	};
}


#endif

