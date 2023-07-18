#pragma once
#ifndef CAMERA_PERSPECTIVE_HPP
#define CAMERA_PERSPECTIVE_HPP

#include "../BaseComponents/Camera/Camera.hpp"
#include "../../Config/Settings.hpp"

using namespace base_component;

namespace camera
{
	class Perspective : public Camera
	{
	public:
		Perspective();
		glm::mat4 GetProjectionMatrix() { return projection_matrix; }
		void SetProjectionMatrix(float FOV);

	private:
		glm::mat4 projection_matrix;
		float FOV;
		float aspectRatio;
	};
}


#endif

