#pragma once
#include <unordered_map>
#include "record.h"
#include "archetype_manager.h"

class EntityManager
{
public:
	std::unordered_map<EntityId, Record> entityIndex;
	ArchetypeManager archetypeManager;
	EntityManager();
	EntityId CreateNewEntity();
	void AddComponent(EntityId entityId, ComponentId componentId, void* data);
	void RemoveComponent(EntityId entityId, ComponentId componentId, void* data);
	void* GetComponent(EntityId entityId,ComponentId componentId);
	void* GetComponent(Record* entityRecord, ComponentId componentId);
	//Sets a new instance of the component data.
	void SetComponent(EntityId entityId,ComponentId componentId, void* data);
	void SetComponent(Record* entityRecord, ComponentId componentId, void* data);
private:
	void edgeAdd(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);
	void edgeRemove(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);
	EntityId entityIdState;
};