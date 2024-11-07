#include "EntityManager.h"
#include "../sceneSystem/entity/id.h"
#include <algorithm>
#include <stdexcept>
#include <string>

EntityId EntityManager::CreateNewEntity()
{
	entitiesCount++;
	EntityId entityId = _entityIdState;
	_entityIdState++;

	// Find default archetype (contains only Id of the entity).
	ComponentId idComponent(type_index(typeid(Id)));
	ArchetypeType type({ idComponent });

	auto result = archetypeManager.GetArchetypeByType(type);
	Archetype* archetype;

	if (result.has_value())
	{
		archetype = result.value();
	}
	else
	{ // Doesn't exist so we create it.
		ArchetypeManager::RegisterComponentType<Id>();
		archetype = archetypeManager.GenerateArchetype(move(type));
	}

	// Create Entity
	size_t entityRow = archetype->CreateEntity();
	ArchetypeManager::pushBack[typeid(Id)](archetype->components[typeid(Id)], new Id(entityId));
	entityIndex.try_emplace(entityId, archetype, entityRow);

	return entityId;
}

void EntityManager::edgeAdd(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId)
{
	auto edgeIterator = oldArchetype->edges.find(componentId);
	if (edgeIterator != oldArchetype->edges.end())
	{
		edgeIterator->second.add = newArchetype;
	}
	else
	{
		ArchetypeEdge edge;
		edge.add = newArchetype;
		oldArchetype->edges[componentId] = edge;
	}
}

void EntityManager::edgeRemove(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId)
{
	auto edgeIterator = oldArchetype->edges.find(componentId);
	if (edgeIterator != oldArchetype->edges.end())
	{
		edgeIterator->second.rmv = newArchetype;
	}
	else
	{
		ArchetypeEdge edge;
		edge.rmv = newArchetype;
		oldArchetype->edges[componentId] = edge;
	}
}

void* EntityManager::GetComponent(EntityId entityId, ComponentId componentId)
{
	auto entityIterator = entityIndex.find(entityId);

	// Read entity record.
	if (entityIterator != entityIndex.end())
	{
		return GetComponent(&entityIterator->second, componentId);
	}
	else
	{
		throw runtime_error("Entity Not Found, Id :" + to_string(entityId));
	}
}

void* EntityManager::GetComponent(Record* entityRecord, ComponentId componentId)
{
	Archetype* archetype = entityRecord->archetypePtr;
	return ArchetypeManager::getRow[componentId](archetype->components[componentId], entityRecord->row);
}

void EntityManager::SetComponent(EntityId entityId, ComponentId componentId, void* data)
{
	auto entityIterator = entityIndex.find(entityId);

	// Read entity record.
	if (entityIterator != entityIndex.end())
	{
		Record& entityRecord = entityIterator->second;
		SetComponent(entityRecord, componentId, data);
	}
	else
	{
		throw runtime_error("Entity Not Found, Id :" + to_string(entityId));
	}
}

void EntityManager::SetComponent(Record& entityRecord, ComponentId componentId, void* data)
{
	Archetype* archetype = entityRecord.archetypePtr;
	ArchetypeManager::insert[componentId](archetype->components[componentId], entityRecord.row, data);
}

void EntityManager::AddComponent(EntityId entityId, ComponentId componentId, void* data)
{
	auto entityIterator = entityIndex.find(entityId);

	// Read entity record.
	Record* record = nullptr;
	if (entityIterator != entityIndex.end())
	{
		record = &entityIterator->second;
	}
	else
	{
		throw runtime_error("Entity Not Found, Id :" + to_string(entityId));
	}

	Archetype* oldArchetype = record->archetypePtr;
	Archetype* newArchetype = nullptr;

	// Use Cache If exists so we don't need to waste time on search.
	auto edgeComponentIterator = oldArchetype->edges.find(componentId);

	if (edgeComponentIterator != oldArchetype->edges.end() && edgeComponentIterator->second.add != nullptr)
	{
		newArchetype = edgeComponentIterator->second.add;
	}
	else // Cache Doesn't Exist We need to create one.
	{
		ArchetypeType newType(*oldArchetype->type); // Clone The Type.

		// Define the new type after adding component
		if (find(newType.begin(), newType.end(), componentId) != newType.end())
		{
			// Component Already Exists !!
			return;
		}

		newType.push_back(componentId);
		sort(newType.begin(), newType.end());

		// Create Cache.
		auto result = archetypeManager.GetArchetypeByType(newType);

		if (result.has_value())
		{
			newArchetype = result.value();
		}
		else
		{
			newArchetype = archetypeManager.GenerateArchetype(move(newType));
		}

		edgeAdd(oldArchetype, newArchetype, componentId);
	}

	// Insert a new row into the destination archetype.
	size_t row = newArchetype->CreateEntity();

	// New Record
	Record newRecord(newArchetype, row);

	// Insert data into the created component.
	ArchetypeManager::pushBack[componentId](newArchetype->components[componentId], data);

	// Move overlapping components over to the destination archetype.

	for (auto& component : *oldArchetype->type)
	{
		void* compData = ArchetypeManager::getRow[component](oldArchetype->components[component], record->row);
		ArchetypeManager::pushBack[component](newArchetype->components[component], compData);
	}

	// Remove the entity from the current archetype.
	auto result = oldArchetype->SwapRemoveEntity(record->row);

	if (result.has_value())
	{
		auto entityIterator = entityIndex.find(result.value());

		// Update swapped entity record.
		entityIterator->second.row = record->row;
	}

	// Update entity record.
	entityIndex.insert_or_assign(entityId, newRecord);
}

void EntityManager::RemoveComponent(EntityId entityId, ComponentId componentId, void* data)
{
	auto entityIterator = entityIndex.find(entityId);

	// Read entity record.
	Record* record = nullptr;

	if (entityIterator != entityIndex.end())
	{
		record = &entityIterator->second;
	}
	else {
		throw runtime_error("Entity Not Found, Id :" + to_string(entityId));
	}

	Archetype* oldArchetype = record->archetypePtr;
	Archetype* newArchetype = nullptr;

	// Use Cache If exists so we don't need to waste time on search.
	auto edgeComponentIterator = oldArchetype->edges.find(componentId);
	
	if (edgeComponentIterator != oldArchetype->edges.end() && edgeComponentIterator->second.rmv != nullptr)
	{
		newArchetype = edgeComponentIterator->second.rmv;
	}
	else {
		// Cache Doesn't Exist We need to create one.
		ArchetypeType newType(*oldArchetype->type); // Clone The Type.

		// Define the new type after adding component
		auto compIterator = find(newType.begin(), newType.end(), componentId);

		if (compIterator != newType.end())
		{
			newType.erase(compIterator);
		}
		else // component doesn't exist in the archetype(The archetype will stay the same)
		{
			return;
		}

		// Create Cache.
		auto result = archetypeManager.GetArchetypeByType(newType);

		if (result.has_value())
		{
			newArchetype = result.value();
		}
		else
		{
			newArchetype = archetypeManager.GenerateArchetype(move(newType));
		}
		edgeRemove(oldArchetype, newArchetype, componentId);
	}

	// Insert a new row into the destination archetype.
	size_t row = newArchetype->CreateEntity();

	// Move overlapping components over to the destination archetype.

	for (auto& component : *newArchetype->type)
	{
		ArchetypeManager::pushBack[component](newArchetype->components[component], GetComponent(record, component));
	}

	// Remove the entity from the current archetype.
	auto result = oldArchetype->SwapRemoveEntity(record->row);

	if (result.has_value())
	{
		auto entityIterator = entityIndex.find(result.value());

		// Update swapped entity record.
		entityIterator->second.row = record->row;
	}

	// Update entity record.
	entityIndex.insert_or_assign(entityId, Record(newArchetype, row));
}

bool EntityManager::HasComponent(EntityId entityId, ComponentId componentId)
{
	auto entityIterator = entityIndex.find(entityId);

	// Read entity record.
	if (entityIterator != entityIndex.end())
	{
		return HasComponent(&entityIterator->second, componentId);
	}
	else
	{
		throw runtime_error("Entity Not Found, Id :" + to_string(entityId));
	}
}

bool EntityManager::HasComponent(Record* entityRecord, ComponentId componentId)
{
	Archetype* archetype = entityRecord->archetypePtr;

	// Find the archetypeMap of the component
	auto componentIterator = archetypeManager.componentIndex.find(componentId);

	if (componentIterator == archetypeManager.componentIndex.end())
	{
		return false;
	}
	ArchetypeMap* archetypes = &componentIterator->second;

	// Get the archetypeRecord of the component.
	auto archetypeIterator = archetypes->find(archetype->archetypeId);

	if (archetypeIterator == archetypes->end())
	{
		return false;
	}

	return true;
}
