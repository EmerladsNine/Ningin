#include "components/SpriteRenderer.h"
#include "../scripting/Scriptable.h"
#include "components/TextRenderer.h"
#include "../system/renderer.h"
#include "components/Transform.h"
#include "components/ScriptVec.h"
#include "entity/Children.h"
#include "entity/Parent.h"
#include "entity/Name.h"
#include "entity/Id.h"
#include "World.h"

using namespace std;

vector<void (*)(float)> World::systems;
vector<void (*)(float)> World::lateSystems;

World::World() : entitiesCount(0) {}

void World::InitDefaultComponentSystem()
{
	systems.push_back(RendererSystem);
	systems.push_back(ScriptSystem);
	lateSystems.push_back(ScriptLateSystem);

	ArchetypeManager::RegisterComponentTypeDeleter<Id>();
	ArchetypeManager::RegisterComponentTypeDeleter<Name>();
	ArchetypeManager::RegisterComponentTypeDeleter<Parent>();
	ArchetypeManager::RegisterComponentTypeDeleter<Children>();
	ArchetypeManager::RegisterComponentTypeDeleter<ScriptVec>();

	EntityManager::RegisterComponent<SpriteRenderer>();
	EntityManager::RegisterComponent<Transform>();
	EntityManager::RegisterComponent<TextRenderer>();
}

EntityId World::NewEntity()
{
	entitiesCount++;
	return EntityManager::CreateNewEntity();
}
