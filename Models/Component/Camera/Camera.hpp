#pragma once
#ifndef COMPONENTS_CAMERA_HPP
#define COMPONENTS_CAMERA_HPP

#include "../Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace components
{
	class Camera : public Component
	{
	public:
		Camera(std::string name);

		void SetPosition(glm::vec3 postion);
		void SetCenter(glm::vec3 center);

		void SetPositionAndCenter(glm::vec3 pos, glm::vec3 center);
		void MovePositionAndCenter(glm::vec3 pos, glm::vec3 center);

		glm::mat4 GetViewMatrix();

	private:
		void SetViewMatrix();

	private:
		const glm::vec3 WORLD_UP = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
		glm::vec3 position;
		glm::vec3 center;
		glm::mat4 view_matrix;
	};

}

#endif // !BASE_COMPONENT_CAMERA_HPP


