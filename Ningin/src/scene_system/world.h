#pragma once
#include <cstddef>
#include <vector>
#include "ecs/entity_manager.h"

class World
{
public:
	static std::vector<void (*)(float, EntityManager*)> systems;
	static std::vector<void (*)(float, EntityManager*)> late_systems;
	static void InitDefaultComponentSystem();

	std::size_t entitiesCount;
	EntityManager entityManager;
	World();
	//Return Id of the entity created.
	EntityId NewEntity();
	
};