#include "entity_manager.h"
#include "../components/id.h"
#include <stdexcept>
#include <string>
#include <algorithm>

EntityManager::EntityManager() : entityIdState(0){}

EntityId EntityManager::CreateNewEntity()
{
	EntityId entityId = entityIdState;
	entityIdState++;
	//Find default archetype (contains only Id of the entity).
	ComponentId idComponent(std::type_index(typeid(Id)));
	ArchetypeType type({idComponent});
	auto result = archetypeManager.GetArchetypeByType(type);
	Archetype* archetype;
	if (result.has_value())
	{
		archetype = result.value();
	}
	else
	{
		//Doesn't exist so we create it.

		ArchetypeManager::RegisterComponentTypeDeleter<Id>();
		archetype = archetypeManager.GenerateArchetype(type);
	}

	//Create Entity
	std::size_t entityRow = archetype->CreateEntity();
	archetype->components[0][entityRow] = new Id(entityId);
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
		oldArchetype->edges[componentId] =  edge;
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

template<typename T>
inline void EntityManager::AddComponent(EntityId entityId, void* data)
{
	ComponentId componentId = typeid(T);
	auto entityIterator = entityIndex.find(entityId);
	//Read entity record.
	Record* record = nullptr;
	if (entityIterator != entityIndex.end())
	{
		record = &entityIterator->second;
	}
	else
	{
		throw std::runtime_error("Entity Not Found, Id :"+ std::to_string(entityId));
	}
	Archetype* oldArchetype = record->archetype_ptr;
	Archetype* newArchetype = nullptr;
	//Use Cache If exists so we don't need to waste time on search.
	auto edgeComponentIterator = oldArchetype->edges.find(componentId);
	if (edgeComponentIterator != oldArchetype->edges.end() && edgeComponentIterator->second.add != nullptr)
	{
		newArchetype = edgeComponentIterator->second.add;
	}
	else
	{
		//Cache Doesn't Exist We need to create one.

		ArchetypeType newType(oldArchetype->type); //Clone The Type.
		//Define the new type after adding component
		if (std::find(newType.begin(), newType.end(), componentId) != newType.end())
		{
			//Component Already Exist !!
			return;
		}

		newType.push_back(componentId);
		std::sort(newType.begin(), newType.end());
		
		//Create Cache.
		auto result = archetypeManager.GetArchetypeByType(newType);
		if (result.has_value())
		{
			newArchetype = result.value();
		}
		else
		{
			ArchetypeManager::RegisterComponentTypeDeleter<T>();
			newArchetype = archetypeManager.GenerateArchetype(newType);
		}
		edgeAdd(oldArchetype, newArchetype, componentId);
	}

	//Insert a new row into the destination archetype.
	std::size_t row = newArchetype->CreateEntity();
	//New Record
	Record newRecord(newArchetype, row);

	//Insert data into the created component
	auto componentIterator = std::lower_bound(newArchetype->type->begin(), newArchetype->type->end(), componentId);
	std::size_t column = std::distance(newArchetype->type->begin(), componentIterator);
	newArchetype->components[column][row] = data;

	//Move overlapping components over to the destination archetype.
	std::size_t oldColumnIndex = 0;
	for (auto& component : oldArchetype->type)
	{
		void* compData = oldArchetype->components[oldColumnIndex][record->row];
		SetComponent(&newRecord,component, compData);
		oldColumnIndex++;
	}

	//Remove the entity from the current archetype.
	auto result = newArchetype->SwapRemoveEntity(record->row);
	if (result.has_value())
	{
		auto entityIterator = entityIndex.find(result.value());
		//Update swapped entity record.
		entityIterator->second.row = record->row;
	}
	//Update entity record.
	entityIndex.emplace(entityId, newRecord);
}

template<typename T>
void EntityManager::RemoveComponent(EntityId entityId, void* data)
{
	ComponentId componentId = typeid(T);
	auto entityIterator = entityIndex.find(entityId);
	//Read entity record.
	Record* record = nullptr;
	if (entityIterator != entityIndex.end())
	{
		record = &entityIterator->second;
	}
	else
	{
		throw std::runtime_error("Entity Not Found, Id :" + std::to_string(entityId));
	}
	Archetype* oldArchetype = record->archetype_ptr;
	Archetype* newArchetype = nullptr;
	//Use Cache If exists so we don't need to waste time on search.
	auto edgeComponentIterator = oldArchetype->edges.find(componentId);
	if (edgeComponentIterator != oldArchetype->edges.end() && edgeComponentIterator->second.rmv != nullptr)
	{
		newArchetype = edgeComponentIterator->second.rmv;
	}
	else
	{
		//Cache Doesn't Exist We need to create one.

		ArchetypeType newType(oldArchetype->type); //Clone The Type.
		//Define the new type after adding component
		auto compIterator = std::find(newType.begin(), newType.end(), componentId);
		if (compIterator != newType.end())
		{
			newType.erase(compIterator);
		}
		else
		{
			//component doesn't exist in the archetype.
			//The archetype will stay the same..
			return;
		}

		//Create Cache.
		auto result = archetypeManager.GetArchetypeByType(newType);
		if (result.has_value())
		{
			newArchetype = result.value();
		}
		else
		{
			newArchetype = archetypeManager.GenerateArchetype(newType);
		}
		edgeRemove(oldArchetype, newArchetype, componentId);
	}

	//Insert a new row into the destination archetype.
	std::size_t row = newArchetype->CreateEntity();

	//Move overlapping components over to the destination archetype.
	std::size_t newColumnIndex = 0;
	for (auto& component : newArchetype->type)
	{
		newArchetype->components[newColumnIndex][row] = GetComponent(record,component);
		newColumnIndex++;
	}

	//Remove the entity from the current archetype.
	auto result = newArchetype->SwapRemoveEntity(record->row);
	if (result.has_value())
	{
		auto entityIterator = entityIndex.find(result.value());
		//Update swapped entity record.
		entityIterator->second.row = record->row;
	}
	//Update entity record.
	entityIndex.emplace(entityId, newArchetype, row);
}

template<typename T>
void* EntityManager::GetComponent(EntityId entityId)
{
	ComponentId componentId = typeid(T);
	return GetComponent(entityId, componentId);
}


void* EntityManager::GetComponent(EntityId entityId, ComponentId componentId)
{
	auto entityIterator = entityIndex.find(entityId);
	//Read entity record.
	if (entityIterator != entityIndex.end())
	{
		return GetComponent(&entityIterator->second, componentId);
	}
	else
	{
		throw std::runtime_error("Entity Not Found, Id :" + std::to_string(entityId));
	}	
}

void* EntityManager::GetComponent(Record* entityRecord, ComponentId componentId)
{
	Archetype* archetype = entityRecord->archetype_ptr;
	//Find the archetypeMap of the component
	auto componentIterator = archetypeManager.componentIndex.find(componentId);
	if (componentIterator == archetypeManager.componentIndex.end())
	{
		return nullptr;
	}
	ArchetypeMap* archetypes = &componentIterator->second;

	//Get the archetypeRecord of the component.
	auto archetypeIterator = archetypes->find(archetype->archetypeId);
	if (archetypeIterator == archetypes->end())
	{
		return nullptr;
	}
	ArchetypeRecord* archetypeRecord = &archetypeIterator->second;

	return archetype->components[archetypeRecord->column][entityRecord->row];
}

template<typename T>
void EntityManager::SetComponent(EntityId entityId, void* data)
{
	ComponentId componentId = typeid(T);
	SetComponent(entityId, componentId, data);
}

void EntityManager::SetComponent(EntityId entityId, ComponentId componentId, void* data)
{
	auto entityIterator = entityIndex.find(entityId);
	//Read entity record.
	if (entityIterator != entityIndex.end())
	{
		Record* entityRecord = &entityIterator->second;
		SetComponent(entityRecord, componentId, data);
	}
	else
	{
		throw std::runtime_error("Entity Not Found, Id :" + std::to_string(entityId));
	}
}

void EntityManager::SetComponent(Record* entityRecord, ComponentId componentId, void* data)
{
	Archetype* archetype = entityRecord->archetype_ptr;
	//Find the archetypeMap of the component
	auto componentIterator = archetypeManager.componentIndex.find(componentId);
	if (componentIterator == archetypeManager.componentIndex.end())
	{
		return;
	}
	ArchetypeMap* archetypes = &componentIterator->second;

	//Get the archetypeRecord of the component.
	auto archetypeIterator = archetypes->find(archetype->archetypeId);
	if (archetypeIterator == archetypes->end())
	{
		return;
	}
	ArchetypeRecord* archetypeRecord = &archetypeIterator->second;
	//delete old data
	auto it = ArchetypeManager::deleters.find(componentId);
	if (it != ArchetypeManager::deleters.end()) {
		it->second(archetype->components[archetypeRecord->column][entityRecord->row]);
		//Assign new data.
		archetype->components[archetypeRecord->column][entityRecord->row] = data;
	}
	else {
		throw std::runtime_error("Unknown component type");
	}
}
