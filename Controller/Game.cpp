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
    orthographicCamera->SetCameraPos(glm::vec3(0.0f, 20.0f, 10.0f)); //Set Above Center
    orthographicCamera->SetCenter(glm::vec3(0.0f, 0.0f, 0.0f)); //Point At Center

    CreateLights();

    this->centerObject = new GameObject("3D/sword2.obj", "Shaders/object.vert", "Shaders/object.frag", "3D/sword.png");
    this->centerObject->SetPosition(0.f, 0.f, 0.f);
    this->centerObject->SetScale(0.5f, 0.5f, 0.5f);
}

void Game::CreateLights()
{
    /* POINT LIGHT COLOR IS HARD CODED */
    this->pointLight = new Point(
        "3D/target.obj",                //Mesh 
        "Shaders/light.vert",           //Vertex Shader
        "Shaders/light.frag",           //Frag Shader
        "3D/potion.png",                //Texture
        glm::vec3(0.f, 0.f, -10.f),     //Initial Pos
        glm::vec3(1.f, 0.4f, 0.1f),     //Light Color
        glm::vec3(1.f, 0.4f, 0.1f),     //Ambient Color
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
        glm::vec3(0.f, 0.f, 0.f),      //Initial Pos
        glm::vec3(1.f, 0.0f, 0.0f),     //Light Color
        glm::vec3(1.f, 0.0f, 0.0f),     //Ambient Color
        0.2f,                           //Ambient Str
        0.5f,                           //Spec Str
        16                              //Spec Phong
    );

    this->directionalLight->SetDirection(glm::vec3(4.0f, 11.0f, -3.0f));
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

    //Camera Switch
    if (one_state == GLFW_PRESS)
    {
        this->isPerspective = true;
    }
    //Camera Switch
    if (two_state == GLFW_PRESS)
    {
        this->isPerspective = false;
    }
    //Single Press Space Script
    if (space_state == GLFW_PRESS && !isSpacePressed)
    {
        isSpacePressed = true;
        this->isCenter = !this->isCenter;
    }
    else if (space_state == GLFW_RELEASE)
    {
        isSpacePressed = false;
    }

    //if center == control middle object, else control light
    if (this->isCenter)
    {
        this->centerObject->ProcessInput(this->gameWindow);
    }
    else
    {
        this->pointLight->ProcessInput(this->gameWindow);
    }

    //Catch input from oerspective camera if perspective camera is active
    if (this->isPerspective)
    {
        this->perpectiveCamera->ProcessInput(this->gameWindow);
    }

    //Catch Light intensity input always
    this->directionalLight->ProcessInput(this->gameWindow);
    //Process Input2 only for intensity input, ProcessInput is for orbit movement
    this->pointLight->ProcessInput2(this->gameWindow);
}

void Game::Update(float tDeltaTime)
{
    //Updates Protected by flags, so always update
    this->centerObject->GameObject::Update(tDeltaTime);
    this->pointLight->Update(tDeltaTime);
    this->directionalLight->Update(tDeltaTime);
    this->perpectiveCamera->Update(tDeltaTime);
}

void Game::Render()
{
    glm::mat4 projection_matrix = glm::mat4();
    glm::mat4 view_matrix = glm::mat4();
    glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);

    //if perpective camera is active, get data from the perspective camera, 
    //otherwise get data from the ortho camera
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
    
    //Get Data from point light
    glm::vec3 point_light_pos = this->pointLight->GetPosition();
    glm::vec3 point_light_color = this->pointLight->GetLightColor(this->isCenter);
    glm::vec3 point_ambient_color = this->pointLight->GetAmbientColor(this->isCenter);

    float point_ambient_str = this->pointLight->GetAmbientStr();
    float point_spec_str = this->pointLight->GetSpecStr();
    float point_spec_phong = this->pointLight->GetSpecPhong();
    float point_intensity = this->pointLight->GetIntensity();

    //Get Data from directional light
    glm::vec3 dir_direction = this->directionalLight->GetPosition();
    glm::vec3 dir_light_color = this->directionalLight->GetLightColor(this->isCenter);
    glm::vec3 dir_ambient_color = this->directionalLight->GetAmbientColor(this->isCenter);

    float dir_ambient_str = this->directionalLight->GetAmbientStr();
    float dir_spec_str = this->directionalLight->GetSpecStr();
    float dir_spec_phong = this->directionalLight->GetSpecPhong();
    float dir_intensity = this->directionalLight->GetIntensity();

    //Draw only center and point light
    this->centerObject->Draw(view_matrix, projection_matrix, point_light_pos, point_light_color,
        point_ambient_str, point_ambient_color, point_spec_str, point_spec_phong, point_intensity,
        dir_direction, dir_light_color, dir_ambient_str, dir_ambient_color, dir_spec_str, 
        dir_spec_phong, dir_intensity, camera_pos);

    this->pointLight->Draw(view_matrix, projection_matrix, point_light_color);
}