#pragma once
#include <cstddef>
#include <vector>
#include "ecs/entity_manager.h"

class World
{
public:
	std::size_t entitiesCount;
	std::vector<void (*)(float, EntityManager*)> systems;
	std::vector<void (*)(float, EntityManager*)> late_systems;
	EntityManager entityManager;
	World();
	void InitDefaultComponentSystem();
	//Return Id of the entity created.
	EntityId NewEntity();
	
};