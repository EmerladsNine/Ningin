#pragma once
#include "archetype_edge.h"
#include <cstddef>
#include <optional>
#include <typeindex>
#include <unordered_map>
#include <vector>

using ComponentId = std::type_index;
using Column = std::vector<void *>;
using ArchetypeType = std::vector<ComponentId>;
using EntityId = size_t;

class Archetype
{
  public:
    size_t archetypeId;
    ArchetypeType *type;
    std::vector<Column> components;                       // The Data of the entities of this archetype.
    std::unordered_map<ComponentId, ArchetypeEdge> edges; // Cache for adding / removing components.
    Archetype(size_t archetypeId, ArchetypeType *type);
    ~Archetype();
    // Returns row of the entity.
    std::size_t CreateEntity();
    // Returns Entity Id of the swapped row or nullopt if no rows were swapped.
    std::optional<EntityId> SwapRemoveEntity(std::size_t row);

  private:
    EntityId GetEntityId(std::size_t row);
    size_t current_row;
};
