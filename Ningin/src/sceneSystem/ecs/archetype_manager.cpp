#include "ArchetypeManager.h"

unordered_map<type_index, function<void(void*)>> ArchetypeManager::deleters;

ArchetypeManager::ArchetypeManager() : archetypeCount(0) {}

optional<Archetype*> ArchetypeManager::GetArchetypeByType(const ArchetypeType& type)
{
	auto iterator = archetypeIndex.find(type);

	// if the iterator doesn't equal end of the map then archetype exists.
	if (iterator != archetypeIndex.end()) {
		return &(iterator->second);
	}
	else {
		return nullopt;
	}
}

Archetype* ArchetypeManager::GenerateArchetype(ArchetypeType type)
{
	ArchetypeId archetypeId = archetypeCount;
	archetypeCount++;

	auto [it, inserted] = archetypeIndex.try_emplace(type, archetypeId, &type); // Create Archetype instance
	Archetype& archetype = it->second;

	uint32_t i = 0; // update component index

	for (auto& componentId : type) {
		auto iterator = componentIndex.find(componentId);
		if (iterator != componentIndex.end()) { // Component exists we can update it.
			ArchetypeMap& archetypeMap = iterator->second;
			archetypeMap.try_emplace(archetypeId, &archetype, i);
		}
		else { // Component doesn't exist we should create its archetype map.
			ArchetypeMap archetypeMap;
			archetypeMap.try_emplace(archetypeId, &archetype, i);
			componentIndex.try_emplace(componentId, move(archetypeMap));
		}
		i++;
	}
	return &archetype;
}
