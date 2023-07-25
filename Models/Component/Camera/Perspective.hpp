#pragma once
#ifndef COMPONENTS_CAMERA_PERSPECTIVE_HPP
#define COMPONENTS_CAMERA_PERSPECTIVE_HPP


#include "../../Config/Settings.hpp"
#include "Camera.hpp"

namespace components
{
	class Perspective : public Camera
	{
	public:
		Perspective(std::string name);
		glm::mat4 GetProjectionMatrix();
		void SetProjectionMatrix(float FOV);

	private:
		glm::mat4 projection_matrix;
		const float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
	};
}


#endif

