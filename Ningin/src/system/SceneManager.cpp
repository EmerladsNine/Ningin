#include "SceneManager.h"

SceneManager::SceneManager(Scene* currentScene) : currentScene(currentScene)
{
}

void SceneManager::NewFrame(float deltaTime)
{
	currentScene->NewFrame(deltaTime);
}
