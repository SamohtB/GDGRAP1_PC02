#pragma once
#ifndef CAMERA_ORTHO_HPP
#define CAMERA_ORTHO_HPP

#include "../BaseComponents/Camera/Camera.hpp"

using namespace base_component;

namespace camera
{
	class Orthographic : public Camera
	{
	public:
		Orthographic();
		glm::mat4 GetProjectionMatrix() { return projection_matrix; }
		void SetProjectionMatrix(float left, float right, float bottom, float top, float near, float far);

	private:
		glm::mat4 projection_matrix;

	};
}

#endif // !CAMERA_ORTHO_HPP



