#pragma once

#include "World.h"
#include "../utils/Timer.h"
#include <string>

using namespace std;

class Scene
{
	public:
		Scene(string name);

		void NewFrame(float deltatime);

		string name;
		World world;

};
