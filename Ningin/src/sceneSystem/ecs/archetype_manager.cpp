#include "ArchetypeManager.h"

unordered_map<type_index, function<void(void*)>> ArchetypeManager::deleters;

ArchetypeManager::ArchetypeManager() : _archetypeCount(0) {}

optional<Archetype*> ArchetypeManager::GetArchetypeByType(const ArchetypeType& type)
{
	auto iterator = archetypeIndex.find(type);

	// if the iterator doesn't equal end of the map then archetype exists.
	if (iterator != archetypeIndex.end())
	{
		return &(iterator->second);
	}
	else
	{
		return nullopt;
	}
}

Archetype* ArchetypeManager::GenerateArchetype(ArchetypeType&& type)
{
	ArchetypeId archetypeId = _archetypeCount;
	_archetypeCount++;

	// Create Archetype instance
	auto [it, inserted] = archetypeIndex.try_emplace(move(type), archetypeId, nullptr);

	Archetype& archetype = it->second;
	archetype.type = &it->first;

	uint32_t i = 0; // update component index

	for (auto& componentId : it->first)
	{
		archetype.components.push_back(Column());
		auto iterator = componentIndex.find(componentId);

		if (iterator != componentIndex.end()) // Component exists we can update it.
		{
			ArchetypeMap& archetypeMap = iterator->second;
			archetypeMap.try_emplace(archetypeId, &archetype, i);
		}
		else // Component doesn't exist we should create its archetype map.
		{
			ArchetypeMap archetypeMap;
			archetypeMap.try_emplace(archetypeId, &archetype, i);
			componentIndex.try_emplace(componentId, move(archetypeMap));
		}

		i++;
	}

	return &archetype;
}
