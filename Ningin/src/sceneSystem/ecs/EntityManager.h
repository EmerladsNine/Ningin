#pragma once

#include "ArchetypeManager.h"
#include <unordered_map>
#include "Record.h"

using namespace std;

class EntityManager
{
	public:
		static EntityId CreateNewEntity();

		template <typename T> static void DefineComponent();

		static void AddComponent(EntityId entityId, ComponentId componentId, void* data);
		static void RemoveComponent(EntityId entityId, ComponentId componentId, void* data);

		static void* GetComponent(EntityId entityId, ComponentId componentId);
		static void* GetComponent(Record* entityRecord, ComponentId componentId);

		// Sets a new instance of the component data.
		static void SetComponent(EntityId entityId, ComponentId componentId, void* data);
		static void SetComponent(Record& entityRecord, ComponentId componentId, void* data);

		static unordered_map<EntityId, Record> entityIndex;
		static ArchetypeManager archetypeManager;

	private:
		static void edgeRemove(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);
		static void edgeAdd(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);

		static EntityId _entityIdState;
};

template<typename T> inline void EntityManager::DefineComponent()
{
	ArchetypeManager::RegisterComponentTypeDeleter<T>();
}
