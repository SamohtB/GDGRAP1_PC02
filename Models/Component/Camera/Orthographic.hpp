#pragma once
#ifndef COMPONENTS_CAMERA_ORTHO_HPP
#define COMPONENTS_CAMERA_ORTHO_HPP

#include "Camera.hpp"

namespace components
{
	class Orthographic : public Camera
	{
		public:
			Orthographic(std::string name);
			glm::mat4 GetProjectionMatrix();
			void SetProjectionMatrix(float left, float right, float bottom, float top, float near, float far);

		private:
			glm::mat4 projection_matrix;
	};
}

#endif // !CAMERA_ORTHO_HPP



