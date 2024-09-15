#pragma once

#include "../sceneSystem/Scene.h"
#include "../utills/Timer.h"

class SceneManager
{
	public:
		SceneManager(Scene* currentScene);

		void NewFrame(Timer timer);

		Scene* currentScene;
};
