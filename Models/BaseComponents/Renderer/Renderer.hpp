#pragma once
#ifndef BASE_COMPONENT_RENDERER_HPP
#define BASE_COMPONENT_RENDERER_HPP

#include "../../tiny_obj_loader.h"
#include "../../stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace base_component
{
	class Renderer
	{
		public:
			Renderer(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_Path);
			~Renderer();

		public:
			void Draw(glm::mat4 transform_matrix, glm::mat4 view_matrix, glm::mat4 projection_matrix,
				glm::vec3 light_pos, glm::vec3 light_color, float ambient_str, glm::vec3 ambient_color,
				glm::vec3 camera_pos, float spec_str, float spec_phong);
			void Draw(glm::mat4 transform_matrix, glm::mat4 view_matrix, glm::mat4 projection_matrix, 
				glm::vec3 light_color);
			void LoadShaders(string Vert_Path, string Frag_Path);
			void LoadMesh(string Mesh_Path);
			void LoadTexture(string Tex_Path);
			void LoadVertices();

		private:
			GLuint VAO;
			GLuint VBO;
			GLuint shaderProgram;
			GLuint texture;

			tinyobj::attrib_t attributes;
			vector<GLuint> mesh_indices;
			vector<GLfloat> fullVertexData;

			int img_width;
			int img_height;
			int colorChannels;
	};
}

#endif


