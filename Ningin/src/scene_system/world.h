#pragma once
#include "ecs/entity_manager.h"
#include <cstddef>
#include <vector>

class World
{
public:
	static std::vector<void (*)(float, EntityManager*)> systems;
	static std::vector<void (*)(float, EntityManager*)> lateSystems;
	static void InitDefaultComponentSystem();

	std::size_t entitiesCount;
	EntityManager entityManager;
	World();
	// Return Id of the entity created.
	EntityId NewEntity();
};
