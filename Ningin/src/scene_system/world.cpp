#include "world.h"

std::vector<void (*)(float, EntityManager*)> World::systems;
std::vector<void (*)(float, EntityManager*)> World::late_systems;

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