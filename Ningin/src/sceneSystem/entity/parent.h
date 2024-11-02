#pragma once

#include "../../ecs/Archetype.h"

class Parent
{
	public:
		Parent(EntityId parentId);

		EntityId parentId;
};
