#include "Scene.h"

Scene::Scene(string name) : name(name) {}

void Scene::NewFrame(float deltaTime)
{
	// Systems
	for (auto& system : World::systems)
	{
		system(&world.entityManager, deltaTime);
	}

	// Late systems.
	for (auto& system : World::lateSystems)
	{
		system(&world.entityManager, deltaTime);
	}
}
