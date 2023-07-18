#pragma once
#ifndef BASE_COMPONENT_CAMERA_HPP
#define BASE_COMPONENT_CAMERA_HPP

#include "../Transform/Transform.hpp"
#include "../Transform//EnumRotationAxis.hpp"

namespace base_component
{
	class Camera : public Transform
	{
	public:
		Camera();
		void MoveCameraWithCenter(glm::vec3 movement);
		void SetCameraWithCenter(glm::vec3 new_pos);
		glm::mat4 GetViewMatrix() { return this->view_matrix; }

	private:
		void SetViewMatrix() { this->view_matrix = glm::lookAt(GetPosition(), this->orientation, WORLD_UP); }

	private:
		glm::vec3 orientation;
		glm::vec3 WORLD_UP;
		glm::mat4 view_matrix;
	};

}

#endif // !BASE_COMPONENT_CAMERA_HPP


