#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer.hpp"

using namespace base_component;

Renderer::Renderer(std::string Mesh_Path, std::string Vert_Path, std::string Frag_Path, std::string Tex_Path)
{
	LoadShaders(Vert_Path, Frag_Path);
	LoadMesh(Mesh_Path);
	LoadVertices();
	LoadTexture(Tex_Path);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VAO);
}

void Renderer::LoadShaders(string Vert_Path, string Frag_Path)
{
    fstream vertSrc(Vert_Path);
    stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    fstream fragSrc(Frag_Path);
    stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    glLinkProgram(shaderProgram);

    this->shaderProgram = shaderProgram;
}

void Renderer::LoadMesh(string Mesh_Path)
{
    string path = Mesh_Path;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> material;
    string warning, error;

    bool success = tinyobj::LoadObj(
        &this->attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str());

    if (!success)
    {
        cerr << "FAILED TO LOAD MESH: " << Mesh_Path << endl;
    }

    for (size_t i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        this->mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    for (size_t i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        fullVertexData.push_back(attributes.vertices[vData.vertex_index * 3]);      // X pos
        fullVertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 1]);  // Y pos
        fullVertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 2]);  // Z pos

        fullVertexData.push_back(attributes.normals[vData.normal_index * 3]);       // R nor
        fullVertexData.push_back(attributes.normals[vData.normal_index * 3 + 1]);   // S nor
        fullVertexData.push_back(attributes.normals[vData.normal_index * 3 + 2]);   // T nor

        fullVertexData.push_back(attributes.texcoords[vData.texcoord_index * 2]);       // U tex
        fullVertexData.push_back(attributes.texcoords[vData.texcoord_index * 2 + 1]);   // V tex
    }
}

void Renderer::LoadVertices()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glUseProgram(this->shaderProgram);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * this->fullVertexData.size(), this->fullVertexData.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);

    GLuint normalsPtr = 3 * sizeof(GLfloat);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)normalsPtr);

    GLuint uvPtr = 6 * sizeof(GLfloat);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)uvPtr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::LoadTexture(string Tex_Path)
{
    stbi_set_flip_vertically_on_load(true);

    const char* path = Tex_Path.c_str();
    unsigned char* tex_bytes = stbi_load(path, &this->img_width, &this->img_height, &this->colorChannels, 0);

    glGenTextures(1, &this->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->img_width, this->img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(tex_bytes);
}

void Renderer::Draw(glm::mat4 transform_matrix, glm::mat4 view_matrix, glm::mat4 projection_matrix,
    glm::vec3 point_light_pos, glm::vec3 point_light_color, float point_ambient_str,
    glm::vec3 point_ambient_color, float point_spec_str, float point_spec_phong, float point_intensity, 
    glm::vec3 dir_direction, glm::vec3 dir_light_color, float dir_ambient_str, glm::vec3 dir_ambient_color,
    float dir_spec_str, float dir_spec_phong, float dir_intensity, glm::vec3 camera_pos)
{
    glUseProgram(this->shaderProgram);

    unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_matrix));

    unsigned int viewLoc = glGetUniformLocation(this->shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));

    unsigned int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

    GLuint tex0Address = glGetUniformLocation(this->shaderProgram, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glUniform1i(tex0Address, 0);

    GLuint pointLightAddress = glGetUniformLocation(this->shaderProgram, "pointLightPos");
    glUniform3fv(pointLightAddress, 1, glm::value_ptr(point_light_pos));

    GLuint pointLightColorAddress = glGetUniformLocation(this->shaderProgram, "pointLightColor");
    glUniform3fv(pointLightColorAddress, 1, glm::value_ptr(point_light_color));

    GLuint pointAmbientStrAddress = glGetUniformLocation(this->shaderProgram, "pointAmbientStr");
    glUniform1f(pointAmbientStrAddress, point_ambient_str);

    GLuint pointAmbientColorAddress = glGetUniformLocation(this->shaderProgram, "pointAmbientColor");
    glUniform3fv(pointAmbientColorAddress, 1, glm::value_ptr(point_ambient_color));

    GLuint pointSpecStrAddress = glGetUniformLocation(this->shaderProgram, "pointSpecStr");
    glUniform1f(pointSpecStrAddress, point_spec_str);

    GLuint pointSpecPhongAddress = glGetUniformLocation(this->shaderProgram, "pointSpecPhong");
    glUniform1f(pointSpecPhongAddress, point_spec_phong);

    GLuint pointIntensityAddress = glGetUniformLocation(this->shaderProgram, "pointIntensity");
    glUniform1f(pointIntensityAddress, point_intensity);

    GLuint dirLightAddress = glGetUniformLocation(this->shaderProgram, "direction");
    glUniform3fv(dirLightAddress, 1, glm::value_ptr(dir_direction));

    GLuint dirLightColorAddress = glGetUniformLocation(this->shaderProgram, "dirLightColor");
    glUniform3fv(dirLightColorAddress, 1, glm::value_ptr(dir_light_color));

    GLuint dirAmbientStrAddress = glGetUniformLocation(this->shaderProgram, "dirAmbientStr");
    glUniform1f(dirAmbientStrAddress, dir_ambient_str);

    GLuint dirAmbientColorAddress = glGetUniformLocation(this->shaderProgram, "dirAmbientColor");
    glUniform3fv(dirAmbientColorAddress, 1, glm::value_ptr(dir_ambient_color));

    GLuint dirSpecStrAddress = glGetUniformLocation(this->shaderProgram, "dirSpecStr");
    glUniform1f(dirSpecStrAddress, dir_spec_str);

    GLuint dirSpecPhongAddress = glGetUniformLocation(this->shaderProgram, "dirSpecPhong");
    glUniform1f(dirSpecPhongAddress, dir_spec_phong);

    GLuint intensityAddress = glGetUniformLocation(this->shaderProgram, "dirIntensity");
    glUniform1f(intensityAddress, dir_intensity);

    GLuint cameraPosAddress = glGetUniformLocation(this->shaderProgram, "cameraPos");
    glUniform3fv(cameraPosAddress, 1, glm::value_ptr(camera_pos));

    glBindVertexArray(this->VAO);

    glDrawArrays(GL_TRIANGLES, 0, this->fullVertexData.size() / 8);
}

void Renderer::Draw(glm::mat4 transform_matrix, glm::mat4 view_matrix, glm::mat4 projection_matrix,
    glm::vec3 light_color)
{
    glUseProgram(this->shaderProgram);

    unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_matrix));

    unsigned int viewLoc = glGetUniformLocation(this->shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));

    unsigned int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

    unsigned int lightColorLoc = glGetUniformLocation(this->shaderProgram, "lightColor");
    glUniform3fv(lightColorLoc, 1, glm::value_ptr(light_color));

    glBindVertexArray(this->VAO);

    glDrawArrays(GL_TRIANGLES, 0, this->fullVertexData.size() / 8);

}