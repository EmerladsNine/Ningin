#pragma once
#include "../ecs/archetype.h"
class Parent
{
public:
	EntityId parentId;
	Parent(EntityId parentId);
};