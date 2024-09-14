#pragma once

#include "../ecs/Archetype.h"
#include <vector>

using namespace std;

class Children
{
	public:
		Children(vector<EntityId> children);

		vector<EntityId> children;
};
