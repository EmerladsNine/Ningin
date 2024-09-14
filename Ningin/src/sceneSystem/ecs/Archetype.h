#pragma once

#include "ArchetypeEdge.h"
#include <unordered_map>
#include <typeindex>
#include <optional>
#include <cstddef>
#include <vector>

using namespace std;

using ComponentId = type_index;
using Column = vector<void*>;
using ArchetypeType = vector<ComponentId>;
using EntityId = size_t;

class Archetype
{
	public:
		Archetype(size_t archetypeId, ArchetypeType* type);
		~Archetype();

		size_t CreateEntity(); // Returns row of the entity.

		// Returns Entity Id of the swapped row or nullopt if no rows were swapped.
		optional<EntityId> SwapRemoveEntity(size_t row);

		unordered_map<ComponentId, ArchetypeEdge> edges; // Cache for adding / removing components.
		vector<Column> components; // The Data of the entities of this archetype.
		const ArchetypeType* type;
		size_t archetypeId;

	private:
		EntityId GetEntityId(size_t row);
};
