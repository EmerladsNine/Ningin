#pragma once
#include "../ecs/archetype.h"
#include <vector>
class Children
{
  public:
    std::vector<EntityId> children;
    Children(std::vector<EntityId> children);
};
