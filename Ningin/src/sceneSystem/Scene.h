#pragma once

#include "World.h"
#include <string>

using namespace std;

class Scene
{
	public:
		Scene(string name);

		void NewFrame(float deltaTime);

		string name;
		World world;

};
