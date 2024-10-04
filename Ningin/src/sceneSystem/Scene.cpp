#include "Scene.h"

Scene::Scene(string name) : name(name) {}

void Scene::NewFrame(float deltatime)
{
	// Systems
	for (auto& system : World::systems)
	{
		system(deltatime);
	}

	// Late systems.
	for (auto& system : World::lateSystems)
	{
		system(deltatime);
	}
}
