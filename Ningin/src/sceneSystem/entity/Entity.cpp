#include "Entity.h"

void EntityGetTransform(EntityId entityId, Transform** transform)
{
	*transform = static_cast<Transform*>(EntityManager::GetComponent(entityId, typeid(Transform)));
}

void EntitySetTransform(EntityId entityId, Transform** transform)
{
	EntityManager::SetComponent(entityId, typeid(Transform), transform);
}

bool EntityHasComponent(EntityId entityId, MonoReflectionType* type)
{
	MonoType* managedType = mono_reflection_type_get_type(type);
	return Mono::HasComponent[managedType](entityId);
}

void EntityGetComponent(EntityId entityId, MonoReflectionType* type, void** data)
{
	MonoType* managedType = mono_reflection_type_get_type(type);
	*data = Mono::GetComponent[managedType](entityId);
}
