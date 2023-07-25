#pragma once
#ifndef COMPONENT_RENDERER_HPP
#define COMPONENT_RENDERER_HPP

#include "../../tiny_obj_loader.h"
#include "../../stb_image.h"
#include "../Component.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

namespace components
{
	class Renderer : public Component
	{
		public:
			Renderer(std::string name);
			~Renderer();

		public:
			void SetMesh(std::string Mesh_Path);
			void SetVertexShader(std::string Vert_Path);
			void SetFragmentShader(std::string Frag_Path);
			void SetTexture(std::string Tex_Path);

			void SetTransformMatrix(const glm::mat4& matrix);
			void SetViewMatrix(const glm::mat4& matrix);
			void SetProjectionMatrix(const glm::mat4& matrix);

			void SetLightPos(const glm::vec3& pos);
			void SetLightColor(const glm::vec3& color);
			void SetAmbientColor(const glm::vec3& color);
			void SetCameraPos(const glm::vec3& pos);

			void SetAmbientStrength(float strength);
			void SetSpecularStrength(float strength);
			void SetSpecularPhong(float phong);

			void SetTextured(bool textured);
			void SetLit(bool lit);
			void SetColored(bool colored);
			
			void Initialize();
			void LoadShaders();
			void LoadMesh();
			void LoadTexture();
			void LoadVertices();

			void Perform() override;

		private:
			std::string meshPath;
			std::string vertPath;
			std::string fragPath;
			std::string texPath;

			glm::mat4 transform_matrix;
			glm::mat4 view_matrix;
			glm::mat4 projection_matrix;

			glm::vec3 light_pos;
			glm::vec3 light_color;
			glm::vec3 ambient_color;
			glm::vec3 camera_pos;

			float ambient_str;
			float spec_str;
			float spec_phong;

			GLuint VAO;
			GLuint VBO;
			GLuint shaderProgram;
			GLuint texture;

			std::vector<GLfloat> fullVertexData;

			bool isTextured;
			bool isLit;
			bool isColored; //for PC02
	};
}

#endif


