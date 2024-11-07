#pragma once

#include "ArchetypeManager.h"
#include <unordered_map>
#include "Record.h"

class EntityManager
{
	public:
		EntityId CreateNewEntity();

		template <typename T> static void RegisterComponent()
		{
			ArchetypeManager::RegisterComponentType<T>();
		}

		void AddComponent(EntityId entityId, ComponentId componentId, void* data);
		void RemoveComponent(EntityId entityId, ComponentId componentId, void* data);

		bool HasComponent(EntityId entityId, ComponentId componentId);
		bool HasComponent(Record* entityRecord, ComponentId componentId);

		void* GetComponent(EntityId entityId, ComponentId componentId);
		void* GetComponent(Record* entityRecord, ComponentId componentId);

		// Sets a new instance of the component data.
		void SetComponent(EntityId entityId, ComponentId componentId, void* data);
		void SetComponent(Record& entityRecord, ComponentId componentId, void* data);

		unordered_map<EntityId, Record> entityIndex;
		ArchetypeManager archetypeManager;

		vector<void (*)(float, ArchetypeManager&)> lateSystems;
		vector<void (*)(float, ArchetypeManager&)> systems;
		size_t entitiesCount;
	private:
		void edgeRemove(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);
		void edgeAdd(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);

		EntityId _entityIdState;
};
