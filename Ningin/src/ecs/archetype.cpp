#include "Archetype.h"
#include "../sceneSystem/entity/Id.h"
#include "ArchetypeManager.h"

Archetype::Archetype(size_t archetype_id, ArchetypeType* type) : archetypeId(archetype_id), type(type)
{
	if (type != nullptr)
	{
		for (auto& componentId : *type)
		{
			components.push_back(Column());
		}
	}
}

size_t Archetype::CreateEntity()
{
	for (auto& column : components)
	{
		column.push_back(nullptr);
	}
	return components[0].size() - 1;
}

optional<EntityId> Archetype::SwapRemoveEntity(size_t row)
{
	if (components.empty())
	{
		return nullopt;
	}

	size_t lastRow = components[0].size() - 1;
	if (row != lastRow)
	{
		for (auto& column : components)
		{
			// Removes row without shifting other rows index. (replaces last row with this row)
			swap(column[row], column[lastRow]);
			column.pop_back();
		}
	}
	else
	{
		for (auto& column : components)
		{
			column.pop_back();
		}
		return nullopt;
	}

	return GetEntityId(row);
}

EntityId Archetype::GetEntityId(size_t row)
{
	Id* id = static_cast<Id*>(components[0][row]);
	return id->id;
}

Archetype::~Archetype()
{
	uint32_t columnIndex = 0;
	for (auto& column : components)
	{
		size_t size = column.size();
		for (size_t row = 0; row < size; row++)
		{
			void* component = column[row];

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
