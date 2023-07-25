#pragma once
#ifndef COMPONENTS_TRANSFORM_HPP
#define COMPONENTS_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Component.hpp"
#include "../../Enum/EnumRotationAxis.hpp"

namespace components
{
	class Transform : public Component
	{
		public:
			Transform(std::string name);

			glm::mat4 GetModelMatrix();

			void Move(float x, float y, float z);
			void Move(glm::vec3 vector);
			void SetPosition(float x, float y, float z);
			void SetPosition(glm::vec3 vector);

			void Rotate(RotationAxis axis, float theta);
			void SetRotation(RotationAxis axis, float theta);

			void Scale(float x, float y, float z);
			void Scale(float scalar);
			void SetScale(float x, float y, float z);
			void SetScale(float scalar);

			glm::vec3 GetPosition() { return this->position; }

		private:
			glm::vec3 position;
			glm::vec3 scale;

			float pitch;
			float yaw;
			float roll;
			
	};
}


#endif

