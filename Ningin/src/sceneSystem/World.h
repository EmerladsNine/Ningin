#pragma once
#include "ecs/EntityManager.h"
#include <cstddef>
#include <vector>

using namespace std;

class World
{
	public:
		World();

		static void InitDefaultComponentSystem();

		EntityId NewEntity(); // Return Id of the entity created.

		static vector<void (*)(float, EntityManager*)> lateSystems;
		static vector<void (*)(float, EntityManager*)> systems;

		EntityManager entityManager;
		size_t entitiesCount;
};
