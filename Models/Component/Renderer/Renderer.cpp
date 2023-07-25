#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer.hpp"

using namespace components;

Renderer::Renderer(std::string name) : Component (name, ComponentType::MESH) 
{
    meshPath = "";
    vertPath = "";
    fragPath = "";
    texPath = "";

    transform_matrix = glm::mat4(1.0f);
    view_matrix = glm::mat4(1.0f);
    projection_matrix = glm::mat4(1.0f);

    light_pos = glm::vec3(0.0f);
    light_color = glm::vec3(0.0f);
    ambient_color = glm::vec3(0.0f);
    camera_pos = glm::vec3(0.0f);

    ambient_str = 0.0f;
    spec_str = 0.0f;
    spec_phong = 0.0f;

    VAO = 0;
    VBO = 0;
    shaderProgram = 0;
    texture = 0;

    isTextured = false;
    isLit = false;
    isColored = false; //for PC02
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VAO);
}

void Renderer::Initialize()
{
    LoadShaders();
    LoadMesh();
    LoadVertices();
    LoadTexture();
}

void Renderer::LoadShaders()
{
    std::fstream vertSrc(this->vertPath);
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    std::fstream fragSrc(this->fragPath);
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
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

void Renderer::LoadMesh()
{
    std::string path = this->meshPath;
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str());

    if (!success)
    {
        std::cerr << "FAILED TO LOAD MESH: " << this->meshPath << std::endl;
    }

    std::vector<GLuint> mesh_indices;

    for (size_t i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
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

void Renderer::LoadTexture()
{
    stbi_set_flip_vertically_on_load(true);

    int img_width;
    int img_height;
    int colorChannels;

    const char* path = this->texPath.c_str();
    unsigned char* tex_bytes = stbi_load(path, &img_width, &img_height, &colorChannels, 0);

    glGenTextures(1, &this->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(tex_bytes);
}

void Renderer::Perform()
{
    glUseProgram(this->shaderProgram);

    unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_matrix));

    unsigned int viewLoc = glGetUniformLocation(this->shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));

    unsigned int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

    if (isTextured)
    {
        GLuint tex0Address = glGetUniformLocation(this->shaderProgram, "tex0");
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glUniform1i(tex0Address, 0);
    }
    
    if (isLit)
    {
        GLuint lightAddress = glGetUniformLocation(this->shaderProgram, "lightPos");
        glUniform3fv(lightAddress, 1, glm::value_ptr(light_pos));

        GLuint lightColorAddress = glGetUniformLocation(this->shaderProgram, "lightColor");
        glUniform3fv(lightColorAddress, 1, glm::value_ptr(light_color));

        GLuint ambientStrAddress = glGetUniformLocation(this->shaderProgram, "ambientStr");
        glUniform1f(ambientStrAddress, ambient_str);

        GLuint ambientColorAddress = glGetUniformLocation(this->shaderProgram, "ambientColor");
        glUniform3fv(ambientColorAddress, 1, glm::value_ptr(ambient_color));

        GLuint cameraPosAddress = glGetUniformLocation(this->shaderProgram, "cameraPos");
        glUniform3fv(cameraPosAddress, 1, glm::value_ptr(camera_pos));

        GLuint specStrAddress = glGetUniformLocation(this->shaderProgram, "specStr");
        glUniform1f(specStrAddress, spec_str);

        GLuint specPhongAddress = glGetUniformLocation(this->shaderProgram, "specPhong");
        glUniform1f(specPhongAddress, spec_phong);
    }

    if (isColored)
    {
        GLuint lightColorAddress = glGetUniformLocation(this->shaderProgram, "lightColor");
        glUniform3fv(lightColorAddress, 1, glm::value_ptr(light_color));
    }
    
    glBindVertexArray(this->VAO);

    glDrawArrays(GL_TRIANGLES, 0, this->fullVertexData.size() / 8);
}

void Renderer::SetMesh(std::string Mesh_Path)
{
    this->meshPath = Mesh_Path;
}

void Renderer::SetVertexShader(std::string Vert_Path)
{
    this->vertPath = Vert_Path;
}

void Renderer::SetFragmentShader(std::string Frag_Path)
{
    this->fragPath = Frag_Path;
}

void Renderer::SetTexture(std::string Tex_Path)
{
    this->meshPath = Tex_Path;
}

void Renderer::SetTransformMatrix(const glm::mat4& matrix) {
    transform_matrix = matrix;
}

void Renderer::SetViewMatrix(const glm::mat4& matrix) {
    view_matrix = matrix;
}

void Renderer::SetProjectionMatrix(const glm::mat4& matrix) {
    projection_matrix = matrix;
}

void Renderer::SetLightPos(const glm::vec3& pos) {
    light_pos = pos;
}

void Renderer::SetLightColor(const glm::vec3& color) {
    light_color = color;
}

void Renderer::SetAmbientColor(const glm::vec3& color) {
    ambient_color = color;
}

void Renderer::SetCameraPos(const glm::vec3& pos) {
    camera_pos = pos;
}

void Renderer::SetAmbientStrength(float strength) {
    ambient_str = strength;
}

void Renderer::SetSpecularStrength(float strength) {
    spec_str = strength;
}

void Renderer::SetSpecularPhong(float phong) {
    spec_phong = phong;
}

void Renderer::SetTextured(bool textured) {
    isTextured = textured;
}

void Renderer::SetLit(bool lit) {
    isLit = lit;
}

void Renderer::SetColored(bool colored) {
    isColored = colored;
}