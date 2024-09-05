#pragma once
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <cstddef>
#include "archetype_edge.h"

using ComponentId = std::type_index;
using Column = std::vector<void*>;
using ArchetypeType = std::vector<ComponentId>;

class Archetype
{
public:
	size_t archetypeId;
	ArchetypeType* type;
	std::vector<Column> components; //The Data of the entities of this archetype.
	std::unordered_map<ComponentId, ArchetypeEdge> edges; //Cache for adding / removing components.
	Archetype(size_t archetypeId, ArchetypeType* type);
	//Returns row of the entity.
	std::size_t CreateEntity();
private:
	size_t current_row;
};