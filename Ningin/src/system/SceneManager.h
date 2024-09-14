#pragma once

#include "../sceneSystem/Scene.h"

class SceneManager
{
	public:
		SceneManager(Scene* currentScene);

		void NewFrame(float deltaTime);

		Scene* currentScene;
};
