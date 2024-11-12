#pragma once

#include "ArchetypeEdge.h"
#include <unordered_map>
#include <optional>
#include <cstddef>
#include <vector>
#include "ComponentId.h"
#include "../sceneSystem/entity/EntityId.h"
#include "util/ECSVector.h"

using namespace std;

using Column = vector<void*>;
using ArchetypeType = vector<ComponentId>;

class Archetype
{
	public:
		Archetype(size_t archetypeId, ArchetypeType* type);
		void Init();
		size_t size;
		size_t CreateEntity(); // Returns row of the entity.

		// Returns Entity Id of the swapped row or nullopt if no rows were swapped.
		optional<EntityId> SwapRemoveEntity(size_t row);

		unordered_map<ComponentId, ArchetypeEdge> edges; // Cache for adding / removing components.
		ECSVector components; // The Data of the entities of this archetype.

		const ArchetypeType* type;
		size_t archetypeId;

	private:
		EntityId GetEntityId(size_t row);
};
