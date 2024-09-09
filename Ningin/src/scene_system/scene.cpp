#include "scene.h"

Scene::Scene(std::string name) : name(name)
{
}

void Scene::NewFrame(float deltaTime)
{
	// Systems
	for (auto& system : World::systems)
	{
		system(deltaTime, &world.entityManager);
	}

	// Late systems.
	for (auto& system : World::late_systems)
	{
		system(deltaTime, &world.entityManager);
	}
}