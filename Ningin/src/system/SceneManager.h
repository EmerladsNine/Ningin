#pragma once

#include "../sceneSystem/Scene.h"

class SceneManager
{
	public:
		Scene currentScene;
		SceneManager(Scene currentScene);
		void NewFrame(float deltaTime);
};
