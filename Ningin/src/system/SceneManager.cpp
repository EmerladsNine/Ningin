#include "SceneManager.h"

namespace Ningin
{
	SceneManager::SceneManager(Scene* currentScene) : currentScene(currentScene) {}

	void SceneManager::NewFrame(float deltatime)
	{
		currentScene->NewFrame(deltatime);
	}
}
