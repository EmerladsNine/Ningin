#pragma once
#include <vector>
#include "../ecs/archetype.h"
class Children
{
public:
	std::vector<EntityId> children;
	Children(std::vector<EntityId> children);
};