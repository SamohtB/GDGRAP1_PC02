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

		void MoveCamera(glm::vec3 movement);
		void SetCameraPos(glm::vec3 new_pos);
		void SetCenter(glm::vec3 orientation);

		glm::mat4 GetViewMatrix() { return this->view_matrix; }

	private:
		void SetViewMatrix();

	private:
		glm::vec3 center;
		glm::vec3 WORLD_UP;
		glm::mat4 view_matrix;
	};

}

#endif // !BASE_COMPONENT_CAMERA_HPP


