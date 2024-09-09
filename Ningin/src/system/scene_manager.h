#pragma once
#include "../scene_system/scene.h"
class SceneManager
{
public:
	Scene currentScene;
	SceneManager(Scene currentScene);
	void NewFrame(float deltaTime);
};
