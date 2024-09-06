#include "archetype_manager.h"

ArchetypeManager::ArchetypeManager() : archetypeCount(0){}

template<typename T>
inline void ArchetypeManager::RegisterComponentTypeDeleter()
{
	ArchetypeManager::deleters[typeid(T)] = [](void* p) { delete static_cast<T*>(p); };
}

std::optional<Archetype*> ArchetypeManager::GetArchetypeByType(const ArchetypeType& type)
{
	auto iterator = archetypeIndex.find(type);
	if (iterator != archetypeIndex.end()) //if the iterator doesn't equal end of the map then archetype exists.
	{
		return &(iterator->second);
	}
	else 
	{
		return std::nullopt;
	}
}

Archetype* ArchetypeManager::GenerateArchetype(ArchetypeType type)
{
	ArchetypeId archetypeId = archetypeCount;
	archetypeCount++;

	//Create Archetype instance
	auto [it, inserted] = archetypeIndex.try_emplace(type, archetypeId, &type);
	Archetype& archetype = it->second;

	//update component index
	uint32_t i = 0;
	for (auto& componentId : type)
	{
		auto iterator = componentIndex.find(componentId);
		if (iterator != componentIndex.end())
		{
			//Component exists we can update it.
			ArchetypeMap& archetypeMap = iterator->second;
			archetypeMap.try_emplace(archetypeId, &archetype, i);
		}
		else
		{
			//Component doesn't exist we should create its archetype map.
			ArchetypeMap archetypeMap;
			archetypeMap.try_emplace(archetypeId, &archetype, i);
			componentIndex.try_emplace(componentId,std::move(archetypeMap));
		}
		i++;
	}
	return &archetype;
}

