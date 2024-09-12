#pragma once
#include "ecs/EntityManager.h"
#include <cstddef>
#include <vector>

class World
{
	public:
		World();

		static std::vector<void (*)(float, EntityManager*)> lateSystems;
		static std::vector<void (*)(float, EntityManager*)> systems;

		EntityManager entityManager;
		std::size_t entitiesCount;

		static void InitDefaultComponentSystem();

		EntityId NewEntity(); // Return Id of the entity created.
};
