#pragma once
#ifndef MODELS_LIGHT_HPP
#define MODELS_LIGHT_HPP

#include "GameObject.hpp"


namespace models
{
	class Light : public GameObject
	{
	public:
		Light(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path, 
			glm::vec3 pos, glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr,
			float specStr, float specPhong);

		void SetLight(glm::vec3 lightColor) { this->lightColor = lightColor; }
		void SetAmbientColor(glm::vec3 ambientColor) { this->ambientColor = ambientColor; }
		void SetAmbientStr(float ambientStr) { this->ambientStr = ambientStr; }
		void SetSpecStr(float specStr) { this->specStr = specStr; }
		void SetSpecPhong(float specPhong) { this->specPhong = specPhong; }
		void IncreaseIntensity(float intensity) { this->intensity += intensity; }

		virtual glm::vec3 GetLightColor(bool isCenter);
		virtual glm::vec3 GetAmbientColor(bool isCenter);
		float GetAmbientStr() { return this->ambientStr; }
		float GetSpecStr() { return this->specStr; }
		float GetSpecPhong() { return this->specPhong; }
		float GetIntensity() { return this->intensity; }

	private:
		glm::vec3 lightColor;
		glm::vec3 ambientColor;
		float ambientStr;
		float specStr;
		float specPhong;
		float intensity;
	};
}

#endif // !MODELS_LIGHT_HPP


