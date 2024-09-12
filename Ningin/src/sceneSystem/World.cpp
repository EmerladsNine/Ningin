#include "components/SpriteRenderer.h"
#include "../scripting/Scriptable.h"
#include "components/TextRenderer.h"
#include "components/Transform.h"
#include "components/ScriptVec.h"
#include "entity/Children.h"
#include "entity/Parent.h"
#include "entity/Name.h"
#include "entity/Id.h"
#include "World.h"

using namespace std;

vector<void (*)(float, EntityManager*)> World::systems;
vector<void (*)(float, EntityManager*)> World::lateSystems;

World::World() : entitiesCount(0) {}

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
	EntityManager::DefineComponent<Transform>();
	EntityManager::DefineComponent<Text>();
}

EntityId World::NewEntity()
{
	entitiesCount++;
	return entityManager.CreateNewEntity();
}
