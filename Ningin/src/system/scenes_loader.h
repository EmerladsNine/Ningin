#pragma once
#include "../scene_system/scene.h"
#include <vector>
#include <cstddef>

class SceneLoader
{
public:
	SceneLoader();
	Scene GetSceneFromId(std::size_t sceneId);
private:
	std::vector<Scene> scenes;
};