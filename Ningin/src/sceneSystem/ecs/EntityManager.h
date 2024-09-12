#pragma once

#include "ArchetypeManager.h"
#include <unordered_map>
#include "Record.h"

using namespace std;

class EntityManager
{
	public:
		EntityManager();

		unordered_map<EntityId, Record> entityIndex;
		ArchetypeManager archetypeManager;

		EntityId CreateNewEntity();

		template <typename T> static void DefineComponent();

		void AddComponent(EntityId entityId, ComponentId componentId, void* data);
		void RemoveComponent(EntityId entityId, ComponentId componentId, void* data);

		void* GetComponent(EntityId entityId, ComponentId componentId);
		void* GetComponent(Record* entityRecord, ComponentId componentId);

		// Sets a new instance of the component data.
		void SetComponent(EntityId entityId, ComponentId componentId, void* data);
		void SetComponent(Record* entityRecord, ComponentId componentId, void* data);

	private:
		void edgeRemove(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);
		void edgeAdd(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);

		EntityId entityIdState;
};

template<typename T> inline void EntityManager::DefineComponent()
{
	ArchetypeManager::RegisterComponentTypeDeleter<T>();
}
