#include "SceneManager.h"

SceneManager::SceneManager(Scene* currentScene) : currentScene(currentScene) {}

void SceneManager::NewFrame(Timer timer)
{
	currentScene->NewFrame(timer);
}
