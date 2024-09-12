#pragma once

#include "World.h"
#include <string>

class Scene
{
	public:
		Scene(std::string name);

		std::string name;
		World world;

		void NewFrame(float deltaTime);
};
