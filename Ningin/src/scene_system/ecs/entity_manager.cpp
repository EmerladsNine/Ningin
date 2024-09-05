#include "entity_manager.h"
#include "../components/id.h"

EntityManager::EntityManager() : entityIdState(0){}

EntityId EntityManager::CreateNewEntity()
{
	EntityId entityId = entityIdState;
	entityIdState++;
	//Find default archetype (contains only Id of the entity).
	ComponentId idComponent(std::type_index(typeid(Id)));
	ArchetypeType type({idComponent});
	Archetype* archetype(archetypeManager.GetArchetypeByType(type));
	std::size_t entityRow = archetype->CreateEntity();
	archetype->components[0][entityRow] = new Id(entityId);
	entityIndex.try_emplace(entityId, archetype, entityRow);
	return entityId;
}
