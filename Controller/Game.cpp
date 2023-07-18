#include "Game.hpp"

using namespace Controller;

Game::Game()
{
    Initialize();

    this->perpectiveCamera = new Perspective();
    this->orthographicCamera = new Orthographic();

    CreateLights();
    CreateObject("3D/sword.obj", "Shaders/object.vert", "Shaders/object.frag", "3D/sword.png");
}

void Game::CreateObject(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_Path)
{
    GameObject* object = new GameObject(Mesh_Path, Vert_Path, Frag_Path, Tex_Path);
    this->gameObjectList.push_back(object);
    object->SetPosition(0.f, 0.f, 0.f);
}

void Game::CreateLights()
{
    this->pointLight = new Point(
        "3D/potion.obj",                //Mesh 
        "Shaders/light.vert",           //Vertex Shader
        "Shaders/light.frag",           //Frag Shader
        "3D/potion.png",                //Texture
        glm::vec3(-10.f, 3.f, 0.f),     //Initial Pos
        glm::vec3(1.f, 1.f, 1.f),       //Light Color
        glm::vec3(1.f, 1.f, 1.f),       //Ambient Color
        0.2f,                           //Ambient Str
        0.5f,                           //Spec Str
        16                              //Spec Phong
    );

    this->directionalLight = new Directional(
        "3D/potion.obj",                //Mesh 
        "Shaders/light.vert",           //Vertex Shader
        "Shaders/light.frag",           //Frag Shader
        "3D/potion.png",                //Texture
        glm::vec3(-10.f, 3.f, 0.f),     //Initial Pos
        glm::vec3(0.f, 0.5f, 0.5f),     //Light Color
        glm::vec3(0.f, 0.5f, 0.5f),     //Ambient Color
        0.2f,                           //Ambient Str
        0.5f,                           //Spec Str
        16                              //Spec Phong
    );
}

void Game::Initialize()
{
    if (!glfwInit())
    {
        exit(-1);
    }

    gameWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Thomas Banatin", NULL, NULL);

    if (!gameWindow)
    {
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(gameWindow);
    gladLoadGL();
}

void Game::Run()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glfwSetTime(0.0f);
    double tLastUpdate = 0.0f;
    float tTimePerFrame = 1.f / FRAME_RATE_LIMIT;

    while (!glfwWindowShouldClose(gameWindow))
    {
        this->ProcessInput();
        tLastUpdate += glfwGetTime();
        glfwSetTime(0.0f);

        while (tLastUpdate > tTimePerFrame)
        {
            tLastUpdate -= tTimePerFrame;
            this->Update(tTimePerFrame);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->Render();

        glfwSwapBuffers(gameWindow);

        glfwPollEvents();
    }
}

void Game::ProcessInput()
{

}

void Game::Update(float tDeltaTime)
{

}

void Game::Render()
{
    glm::mat4 projection_matrix = perpectiveCamera->GetProjectionMatrix();
    glm::mat4 view_matrix = this->perpectiveCamera->GetViewMatrix();
    
    glm::vec3 light_pos = this->pointLight->GetPosition();
    glm::vec3 light_color = this->pointLight->GetLightColor();
    glm::vec3 ambient_color = this->pointLight->GetAmbientColor();

    glm::vec3 camera_pos = this->perpectiveCamera->GetPosition();

    float ambient_str = this->pointLight->GetAmbientStr();
    float spec_str = this->pointLight->GetSpecStr();
    float spec_phong = this->pointLight->GetSpecPhong();

    for (GameObject* object : gameObjectList)
    {
        object->Draw(view_matrix, projection_matrix, light_pos, light_color,
            ambient_str, ambient_color, spec_str, spec_phong, camera_pos);
    }

    this->pointLight->Draw(view_matrix, projection_matrix);
}

void Game::CreateGameObject(string Mesh_Path, string Vert_Path, string Frag_Path, string Tex_path)
{
    GameObject* object = new GameObject(Mesh_Path, Vert_Path, Frag_Path, Tex_path);
    gameObjectList.push_back(object);
}