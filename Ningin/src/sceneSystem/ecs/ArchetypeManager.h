#pragma once

#include "ArchetypeTypeHasher.h"
#include "ArchetypeRecord.h"
#include <unordered_map>
#include "archetype.h"
#include <functional>
#include <typeindex>
#include <stdexcept>
#include <optional>
#include <cstddef>
#include <vector>

using namespace std;

using ArchetypeId = size_t;
using ArchetypeMap = unordered_map<ArchetypeId, ArchetypeRecord>;

class ArchetypeManager
{
	public:
		ArchetypeManager();

		// These are used to remove components data depending on the component type
		static unordered_map<type_index, function<void(void*)>> deleters;

		unordered_map<ArchetypeType, Archetype, VectorHasher> archetypeIndex;
		unordered_map<ComponentId, ArchetypeMap> componentIndex;

		template <typename T> static void RegisterComponentTypeDeleter()
		{
			ArchetypeManager::deleters[typeid(T)] = [](void* p) { delete static_cast<T*>(p); };
		}

		optional<Archetype*> GetArchetypeByType(const ArchetypeType& type);

		Archetype* GenerateArchetype(ArchetypeType type);

	private:
		ArchetypeId archetypeCount;
};
