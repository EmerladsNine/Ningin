#include "Entity.h"

namespace Ningin::Components
{
	bool EntityHasComponent(EntityId entityId, MonoReflectionType* type)
	{
		MonoType* managedType = mono_reflection_type_get_type(type);
		return Mono::HasComponent[managedType](entityId,  SceneManager::currentScene->entityManager);
	}

	void EntityGetComponent(EntityId entityId, MonoReflectionType* type, void** data)
	{
		MonoType* managedType = mono_reflection_type_get_type(type);
		*data = Mono::GetComponent[managedType](entityId, SceneManager::currentScene->entityManager);
	}
}