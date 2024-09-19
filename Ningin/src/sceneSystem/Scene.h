#pragma once

#include "World.h"
#include "../utils/Timer.h"
#include <string>

using namespace std;

class Scene
{
	public:
		Scene(string name);

		void NewFrame(Timer timer);

		string name;
		World world;

};
