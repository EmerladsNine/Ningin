#pragma once
#include "ecs/EntityManager.h"
#include "../utils/Timer.h"
#include <cstddef>
#include <vector>

using namespace std;

class World
{
	public:
		World();

		static void InitDefaultComponentSystem();

		EntityId NewEntity(); // Return Id of the entity created.

		static vector<void (*)(float)> lateSystems;
		static vector<void (*)(float)> systems;
		size_t entitiesCount;
};
