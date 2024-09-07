#pragma once
#include "archetype_record.h"
#include "archetype.h"
#include "archetype_type_hasher.h"
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <functional>
#include <stdexcept>
#include <cstddef>
#include <optional>

using ArchetypeId = std::size_t;
using ArchetypeMap = std::unordered_map<ArchetypeId, ArchetypeRecord>;

class ArchetypeManager
{
public:
	//These are used to remove components data depending on the component type
	static std::unordered_map<std::type_index, std::function<void(void*)>> deleters;
	template<typename T>
	static void RegisterComponentTypeDeleter() {
		ArchetypeManager::deleters[typeid(T)] = [](void* p) { delete static_cast<T*>(p); };
	}
	std::unordered_map<ComponentId, ArchetypeMap> componentIndex;
	std::unordered_map<ArchetypeType, Archetype , VectorHasher> archetypeIndex;
	ArchetypeManager();
	std::optional<Archetype*> GetArchetypeByType(const ArchetypeType& type);
	Archetype* GenerateArchetype(ArchetypeType type);
private:
	ArchetypeId archetypeCount;
};