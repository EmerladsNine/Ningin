#include "Archetype.h"
#include "../entity/Id.h"
#include "ArchetypeManager.h"

Archetype::Archetype(size_t archetype_id, ArchetypeType* type) : archetypeId(archetype_id), type(type),
	current_row(0) {}

size_t Archetype::CreateEntity()
{
	for (auto& column : components) {
		column[current_row] = nullptr;
	}
	return current_row++;
}

optional<EntityId> Archetype::SwapRemoveEntity(size_t row)
{
	if (components.size() == 0) {
		current_row--;
		return nullopt;
	}

	size_t lastRow = components[0].size() - 1;
	for (auto& column : components) {
		// Removes row without shifting other rows index. (replaces last row with this row)
		swap(column[row], column[lastRow]);
		column.pop_back();
	}

	current_row--;
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
	for (auto& column : components) {
		size_t size = column.size();
		for (size_t row = 0; row < size; row++) {
			void* component = column[row];

			auto it = ArchetypeManager::deleters.find((*type)[columnIndex]);
			if (it != ArchetypeManager::deleters.end()) {
				it->second(component);
			}
			else { /*Memory Leak !*/ }
		}
		columnIndex++;
	}
}
