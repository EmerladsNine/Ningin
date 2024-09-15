#pragma once
#include "ecs/EntityManager.h"
#include "../utills/Timer.h"
#include <cstddef>
#include <vector>

using namespace std;

class World
{
	public:
		World();

		static void InitDefaultComponentSystem();

		EntityId NewEntity(); // Return Id of the entity created.

		static vector<void (*)(EntityManager*, Timer)> lateSystems;
		static vector<void (*)(EntityManager*, Timer)> systems;

		EntityManager entityManager;
		size_t entitiesCount;
};
