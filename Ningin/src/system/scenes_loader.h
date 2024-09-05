#pragma once
#include "../scene_system/scene.h"
#include <vector>
#include <cstddef>
#include <string>

class SceneLoader
{
public:
	SceneLoader();
	Scene GetSceneFromId(std::size_t sceneId);
	void LoadSceneFromFile(std::string path);
private:
	std::vector<Scene> scenes;
};