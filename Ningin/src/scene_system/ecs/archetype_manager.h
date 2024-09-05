#pragma once
#include <unordered_map>
#include "archetype_record.h"
#include "archetype.h"
#include "archetype_type_hasher.h"
#include <vector>
#include <cstddef>

using ArchetypeId = std::size_t;
using ArchetypeMap = std::unordered_map<ArchetypeId, ArchetypeRecord>;

class ArchetypeManager
{
public:
	std::unordered_map<ComponentId, ArchetypeMap> componentIndex;
	std::unordered_map<ArchetypeType, Archetype , VectorHasher> archetypeIndex;
	ArchetypeManager();
	Archetype* GetArchetypeByType(const ArchetypeType& type);
private:
	ArchetypeId archetypeCount;
	Archetype* GenerateArchetype(ArchetypeType type);
};