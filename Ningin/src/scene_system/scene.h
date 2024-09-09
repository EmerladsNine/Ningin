#pragma once
#include "world.h"
#include <string>

class Scene
{
public:
	std::string name;
	World world;
	Scene(std::string name);
	void NewFrame(float deltaTime);
};
