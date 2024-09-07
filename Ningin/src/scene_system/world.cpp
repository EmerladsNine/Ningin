#include "world.h"

World::World() : entitiesCount(0)
{
}

void World::InitDefaultComponentSystem()
{
}

EntityId World::NewEntity()
{
    entitiesCount++;
    return entityManager.CreateNewEntity();
}
