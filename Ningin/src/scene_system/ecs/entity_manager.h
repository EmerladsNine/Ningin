#pragma once
#include <unordered_map>
#include "record.h"
#include "archetype_manager.h"

using EntityId = size_t;

class EntityManager
{
public:
	std::unordered_map<EntityId, Record> entityIndex;
	ArchetypeManager archetypeManager;
	EntityManager();
	EntityId CreateNewEntity();
private:
	EntityId entityIdState;
};