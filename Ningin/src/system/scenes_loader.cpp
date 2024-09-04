#include "scenes_loader.h"
#include <iostream>

SceneLoader::SceneLoader(){}

Scene SceneLoader::GetSceneFromId(std::size_t sceneId)
{
    if (sceneId < scenes.size()) {
        return scenes[sceneId];  
    }
    else {
        throw std::out_of_range("Scene ID out of range");
    }
}
