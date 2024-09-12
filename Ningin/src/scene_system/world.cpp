#include "world.h"
#include "../scripting/scriptable.h"
#include "components/id.h"
#include "components/name.h"
#include "components/parent.h"
#include "components/children.h"
#include "components/ScriptVec.h"
#include "components/sprite_renderer.h"
#include "components/text_renderer.h"
#include "components/transform.h"


std::vector<void (*)(float, EntityManager*)> World::systems;
std::vector<void (*)(float, EntityManager*)> World::lateSystems;

World::World() : entitiesCount(0)
{
}

void World::InitDefaultComponentSystem()
{
	systems.push_back(ScriptSystem);
	lateSystems.push_back(ScriptLateSystem);

	EntityManager::DefineComponent<Id>();
	EntityManager::DefineComponent<Name>();
	EntityManager::DefineComponent<Parent>();
	EntityManager::DefineComponent<Children>();
	EntityManager::DefineComponent<ScriptVec>();
	EntityManager::DefineComponent<SpriteRenderer>();
	EntityManager::DefineComponent<Text>();
	EntityManager::DefineComponent<Transform>();
}

EntityId World::NewEntity()
{
	entitiesCount++;
	return entityManager.CreateNewEntity();
}