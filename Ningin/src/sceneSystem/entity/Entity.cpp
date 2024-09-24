#include "Entity.h"

void EntityGetTransform(EntityId entityId, Transform** transform)
{
	*transform = static_cast<Transform*>(EntityManager::GetComponent(entityId, typeid(Transform)));
}

void EntitySetTransform(EntityId entityId, Transform** transform)
{
	EntityManager::SetComponent(entityId, typeid(Transform), transform);
}