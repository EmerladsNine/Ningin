#pragma once
#include <unordered_map>
#include "archetype_record.h"
#include "archetype.h"
#include <vector>
#include <cstddef>

using ComponentId = std::size_t;
using ArchetypeId = std::size_t;
using ArchetypeMap = std::unordered_map<ArchetypeId, ArchetypeRecord>;
using ArchetypeType = std::vector<ComponentId>;

class ArchetypeManager
{
public:
	std::unordered_map<ComponentId, ArchetypeMap> componentIndex;
	std::unordered_map<ArchetypeType, Archetype> archetypeIndex;
	ArchetypeManager();
private:
	ArchetypeId archetypeCount;
};