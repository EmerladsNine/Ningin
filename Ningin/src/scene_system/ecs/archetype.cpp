#include "archetype.h"

Archetype::Archetype(size_t archetype_id, ArchetypeType* type) : archetypeId(archetype_id), type(type), current_row(0){}

std::size_t Archetype::CreateEntity()
{
	for (auto& column : components)
	{
		column[current_row] = nullptr;
	}
	return current_row++;
}
