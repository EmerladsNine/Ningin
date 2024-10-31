#include "components/SpriteRenderer.h"
#include "../scripting/Scriptable.h"
#include "components/TextRenderer.h"
#include "../system/renderer.h"
#include "components/Transform.h"
#include "components/ScriptVec.h"
#include "components/colliders/BoxCollider.h"
#include "components/colliders/CircleCollider.h"
#include "components/colliders/PointCollider.h"
#include "components/colliders/PolygonCollider.h"
#include "entity/Children.h"
#include "entity/Parent.h"
#include "entity/Name.h"
#include "entity/Id.h"

#include "Scene.h"

namespace Ningin
{
	using namespace Components;

	Scene::Scene(string name) : name(name) {}

	void Scene::InitDefaultComponentSystem()
	{
		entityManager.systems.push_back(RendererSystem);
		entityManager.systems.push_back(ScriptSystem);
		entityManager.lateSystems.push_back(ScriptLateSystem);

		EntityManager::RegisterComponent<Id>();
		EntityManager::RegisterComponent<Name>();
		EntityManager::RegisterComponent<Parent>();
		EntityManager::RegisterComponent<Children>();
		EntityManager::RegisterComponent<ScriptVec>();

		RegisterComponent<SpriteRenderer>();
		RegisterComponent<Transform>();
		RegisterComponent<TextRenderer>();

		RegisterComponent<CircleCollider>();
		RegisterComponent<PointCollider>();
		RegisterComponent<PolygonCollider>();
		RegisterComponent<BoxCollider>();
	}

	void Scene::NewFrame(float deltatime)
	{
		ArchetypeManager& archetypeManager = entityManager.archetypeManager;
		// Systems
		for (auto& system : entityManager.systems)
		{
			system(deltatime, archetypeManager);
		}

		// Late systems.
		for (auto& system : entityManager.lateSystems)
		{
			system(deltatime, archetypeManager);
		}
	}
}
