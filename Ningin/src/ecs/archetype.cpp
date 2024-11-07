#include "Archetype.h"
#include "../sceneSystem/entity/Id.h"
#include "ArchetypeManager.h"

Archetype::Archetype(size_t archetype_id, ArchetypeType* type) : archetypeId(archetype_id), type(type) , size(0)
{
	
}

size_t Archetype::CreateEntity()
{
	size++;
	return size - 1;
}

optional<EntityId> Archetype::SwapRemoveEntity(size_t row)
{
	if (components.empty())
	{
		return nullopt;
	}

	size_t lastRow = size - 1;
	size--;
	if (row != lastRow)
	{
		for (auto column : components)
		{
			// Removes row without shifting other rows index. (replaces last row with this row)
			ArchetypeManager::swapRemove[column.first](column.second,row);
		}
	}
	else
	{
		for (auto& column : components)
		{
			ArchetypeManager::removeLast[column.first](column.second);
		}
		return nullopt;
	}

	return GetEntityId(row);
}

EntityId Archetype::GetEntityId(size_t row)
{
	Id* id = static_cast<Id*>( ArchetypeManager::getRow[typeid(Id)](components[typeid(Id)],row));
	return id->id;
}

Archetype::~Archetype()
{
	uint32_t columnIndex = 0;
	for (auto& column : components)
	{
		for (size_t row = 0; row < size; row++)
		{
			void* component = ArchetypeManager::getRow[column.first](column.second,row);

			auto it = ArchetypeManager::deleters.find((*type)[columnIndex]);
			if (it != ArchetypeManager::deleters.end())
			{
				it->second(component);
			}
			else { /*Memory Leak !*/ }
		}

		columnIndex++;
	}
}
