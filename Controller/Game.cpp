#include "Game.hpp"

using namespace Controller;

Game::Game()
{
    Initialize();

    this->isSpacePressed = false;
    this->isPerspective = true;
    this->isCenter = true;

    this->perpectiveCamera = new Perspective();
    this->orthographicCamera = new Orthographic();
    orthographicCamera->SetCameraPos(glm::vec3(0.0f, 20.0f, 10.0f));
    orthographicCamera->SetCenter(glm::vec3(0.0f, 0.0f, 0.0f));

    CreateLights();

    this->centerObject = new GameObject("3D/sword2.obj", "Shaders/object.vert", "Shaders/object.frag", "3D/sword.png");
    this->centerObject->SetPosition(0.f, 0.f, 0.f);
    this->centerObject->SetScale(0.5f, 0.5f, 0.5f);
}

void Game::CreateLights()
{
    this->pointLight = new Point(
        "3D/target.obj",                //Mesh 
        "Shaders/light.vert",           //Vertex Shader
        "Shaders/light.frag",           //Frag Shader
        "3D/potion.png",                //Texture
        glm::vec3(0.f, 0.f, 10.f),     //Initial Pos
        glm::vec3(1.f, 0.4f, 0.1f),       //Light Color
        glm::vec3(1.f, 0.4f, 0.1f),       //Ambient Color
        0.2f,                           //Ambient Str
        0.5f,                           //Spec Str
        16                              //Spec Phong
    );

    this->pointLight->SetScale(5.0f);
    this->pointLight->Rotate(RotationAxis::YAW, 90.f);

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

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
    int space_state = glfwGetKey(this->gameWindow, GLFW_KEY_SPACE);
    int one_state = glfwGetKey(this->gameWindow, GLFW_KEY_1);
    int two_state = glfwGetKey(this->gameWindow, GLFW_KEY_2);

    if (one_state == GLFW_PRESS)
    {
        this->isPerspective = true;
    }
    
    if (two_state == GLFW_PRESS)
    {
        this->isPerspective = false;
    }

    if (space_state == GLFW_PRESS && !isSpacePressed)
    {
        isSpacePressed = true;
        this->isCenter = !this->isCenter;
    }
    else if (space_state == GLFW_RELEASE)
    {
        isSpacePressed = false;
    }


    if (this->isCenter)
    {
        this->centerObject->ProcessInput(this->gameWindow);

    }
    else
    {
        this->pointLight->ProcessInput(this->gameWindow);
    }
}

void Game::Update(float tDeltaTime)
{
    this->centerObject->GameObject::Update(tDeltaTime);
    this->pointLight->Update(tDeltaTime);
}

void Game::Render()
{
    glm::mat4 projection_matrix = glm::mat4();
    glm::mat4 view_matrix = glm::mat4();
    glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);

    if (this->isPerspective)
    {
        projection_matrix = perpectiveCamera->GetProjectionMatrix();
        view_matrix = this->perpectiveCamera->GetViewMatrix();
        camera_pos = this->perpectiveCamera->GetPosition();
    }
    else if (!this->isPerspective)
    {
        projection_matrix = this->orthographicCamera->GetProjectionMatrix();
        view_matrix = this->orthographicCamera->GetViewMatrix();
        camera_pos = this->orthographicCamera->GetPosition();
    }
    
    glm::vec3 light_pos = this->pointLight->GetPosition();
    glm::vec3 light_color = this->pointLight->GetLightColor();
    glm::vec3 ambient_color = this->pointLight->GetAmbientColor();

    float ambient_str = this->pointLight->GetAmbientStr();
    float spec_str = this->pointLight->GetSpecStr();
    float spec_phong = this->pointLight->GetSpecPhong();

    this->centerObject->Draw(view_matrix, projection_matrix, light_pos, light_color,
        ambient_str, ambient_color, spec_str, spec_phong, camera_pos);

    this->pointLight->Draw(view_matrix, projection_matrix, light_color);
}