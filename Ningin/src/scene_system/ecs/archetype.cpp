#include "archetype.h"
#include "archetype_manager.h"
#include "../components/id.h"

Archetype::Archetype(size_t archetype_id, ArchetypeType* type) : archetypeId(archetype_id), type(type), current_row(0) {}

std::size_t Archetype::CreateEntity()
{
	for (auto& column : components)
	{
		column[current_row] = nullptr;
	}
	return current_row++;
}

std::optional<EntityId> Archetype::SwapRemoveEntity(std::size_t row)
{
	if (components.size() == 0)
	{
		current_row--;
		return std::nullopt;
	}
	std::size_t lastRow = components[0].size() - 1;
	for (auto& column : components)
	{
		//Removes row without shifting other rows index. (replaces last row with this row)
		std::swap(column[row], column[lastRow]);
		column.pop_back();
	}
	current_row--;
	return GetEntityId(row);
}

EntityId Archetype::GetEntityId(std::size_t row)
{
	Id* id = static_cast<Id*>(components[0][row]);
	return id->id;
}

Archetype::~Archetype()
{
	uint32_t columnIndex = 0;
	for (auto& column : components)
	{
		std::size_t size = column.size();
		for (std::size_t row = 0; row < size; row++)
		{
			void* component = column[row];

			auto it = ArchetypeManager::deleters.find((*type)[columnIndex]);
			if (it != ArchetypeManager::deleters.end()) {
				it->second(component);
			}
			else {/*Memory Leak !*/ }
		}
		columnIndex++;
	}
}