#include "SceneManager.h"

namespace Ningin
{
	Scene* SceneManager::currentScene;

	void SceneManager::NewFrame(float deltatime)
	{
		currentScene->NewFrame(deltatime);
	}
}
