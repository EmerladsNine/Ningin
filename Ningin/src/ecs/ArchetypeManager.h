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
		static unordered_map<type_index, function<void(void*,void*)>> insert;
		static unordered_map<type_index, function<int()>> sizeOf;

		template <typename T> static void RegisterComponentType()
		{
			ArchetypeManager::deleters[typeid(T)] = [](void* p) { delete static_cast<T*>(p); };

			ArchetypeManager::insert[typeid(T)] = [](void* dest,void* data) 
			{
				T& dataRef = *reinterpret_cast<T*>(data);
				new (dest) T(std::move(dataRef));

				//*static_cast<T*>(dest) = std::move(dataRef);
			};
			
			ArchetypeManager::sizeOf[typeid(T)] = []() -> int
			{
				return sizeof(T);
			};

		}

		optional<Archetype*> GetArchetypeByType(const ArchetypeType& type);

		Archetype* GenerateArchetype(ArchetypeType&& type);

		unordered_map<ArchetypeType, Archetype, VectorHasher> archetypeIndex;
		unordered_map<ComponentId, ArchetypeMap> componentIndex;

	private:
		ArchetypeId _archetypeCount;
};
