#include "Scene.h"

Scene::Scene(string name) : name(name) {}

void Scene::NewFrame(Timer timer)
{
	// Systems
	for (auto& system : World::systems)
	{
		system(&world.entityManager, timer);
	}

	// Late systems.
	for (auto& system : World::lateSystems)
	{
		system(&world.entityManager, timer);
	}
}
