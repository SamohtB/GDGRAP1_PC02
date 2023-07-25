#pragma once
#ifndef COMPONENTS_LIGHT_HPP
#define COMPONENTS_LIGHT_HPP

#include "../Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace components
{
	class Light : public Component
	{
		public:
			Light(std::string name);

			void SetPosition(glm::vec3 position);
			void SetLight(glm::vec3 lightColor);
			void SetAmbientColor(glm::vec3 ambientColor);
			void SetAmbientStr(float ambientStr);
			void SetSpecStr(float specStr);
			void SetSpecPhong(float specPhong);
			void SetIntensity(float intensity);

			glm::vec3 GetPosition();
			glm::vec3 GetLightColor();
			glm::vec3 GetAmbientColor();
			float GetAmbientStr();
			float GetSpecStr();
			float GetSpecPhong();
			float GetIntensity();

		private:
			glm::vec3 position;
			glm::vec3 lightColor;
			glm::vec3 ambientColor;
			float ambientStr;
			float specStr;
			float specPhong;
			float intensity;
	};
}

#endif // !MODELS_LIGHT_HPP


