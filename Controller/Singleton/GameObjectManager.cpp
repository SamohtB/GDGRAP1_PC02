#include "GameObjectManager.hpp"

using namespace controller;

void GameObjectManager::ProcessInput(GLFWwindow* gameWindow)
{
    for (GameObject* object : this->gameObjectList)
    {
        object->ProcessInput(gameWindow);
    }
}

void GameObjectManager::Update(float deltaTime)
{
    for (GameObject* object : this->gameObjectList)
    {
        object->Update(deltaTime);
    }
}

void GameObjectManager::Draw()
{
    for (GameObject* object : this->gameObjectList)
    {
        object->Draw();
    }
}

void GameObjectManager::AddObject(GameObject* gameObject)
{
    this->gameObjectList.push_back(gameObject);
    gameObject->Initialize();
}

void GameObjectManager::DeleteObject(GameObject* gameObject)
{
    std::string strName = gameObject->GetName();
    int nIndex = -1;

    for (int i = 0; i < this->gameObjectList.size() && nIndex == -1; i++) {
        if (this->gameObjectList[i] == gameObject)
            nIndex = i;
    }

    if (nIndex != -1) {
        this->gameObjectList.erase(this->gameObjectList.begin() + nIndex);
        delete gameObject;
    }
}

GameObjectManager* GameObjectManager::Instance = NULL;

GameObjectManager* GameObjectManager::GetInstance() 
{
    if (Instance == NULL)
    {
        Instance = new GameObjectManager();
    }
        
    return Instance;
}