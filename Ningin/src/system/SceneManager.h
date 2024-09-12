#pragma once

#include "../scene_system/Scene.h"

class SceneManager
{
	public:
		Scene currentScene;
		SceneManager(Scene currentScene);
		void NewFrame(float deltaTime);
};
