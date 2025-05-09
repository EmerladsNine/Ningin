#include "Archetype.h"
#include "../sceneSystem/entity/Id.h"
#include "ArchetypeManager.h"

Archetype::Archetype(size_t archetype_id, ArchetypeType* type) : archetypeId(archetype_id), type(type) , size(0)
{
	
}

void Archetype::Init()
{
	int bytes = 0;
	for (auto& componentType : *type)
	{
		components.AddComponentPosition(componentType, bytes);
		bytes += ArchetypeManager::sizeOf[componentType]();
	}
	int entitySize = bytes;
	components.Init(entitySize);
}

size_t Archetype::CreateEntity()
{
	size++;
	components.CreateEntity();
	return size - 1;
}

optional<EntityId> Archetype::SwapRemoveEntity(size_t row)
{
	if (components.Empty())
	{
		return nullopt;
	}

	size_t lastRow = size - 1;
	size--;
	if (row != lastRow)
	{
		components.SwapRemove(row);
	}
	else
	{
		components.PopBack();
		return nullopt;
	}

	return GetEntityId(row);
}

EntityId Archetype::GetEntityId(size_t row)
{
	Id* id = reinterpret_cast<Id*>(components.GetEntityComponentPointer(row, typeid(Id)));
	return id->id;
}
