#pragma once

#include "../ecs/Archetype.h"
#include <vector>

class Children
{
	public:
		Children(std::vector<EntityId> children);

		std::vector<EntityId> children;
};
