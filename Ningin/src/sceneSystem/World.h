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

		static vector<void (*)(Timer)> lateSystems;
		static vector<void (*)(Timer)> systems;
		size_t entitiesCount;
};
