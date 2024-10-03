#pragma once

#include "ArchetypeManager.h"
#include <unordered_map>
#include "Record.h"
#include "../../scripting/ScriptingEngine.h"

class EntityManager
{
	public:
		static EntityId CreateNewEntity();

		template <typename T> static void RegisterComponent()
		{
			//Init Destructor
			ArchetypeManager::RegisterComponentTypeDeleter<T>();
			//Link To C#
			MonoType* managedType = ScriptingEngine::mono.GetComponentManagedType<T>();
			Mono::HasComponent[managedType] = [](EntityId entityId) -> bool { return EntityManager::HasComponent(entityId, typeid(T)); };
			Mono::GetComponent[managedType] = [](EntityId entityId) -> void* { return EntityManager::GetComponent(entityId, typeid(T)); };
		}

		static void AddComponent(EntityId entityId, ComponentId componentId, void* data);
		static void RemoveComponent(EntityId entityId, ComponentId componentId, void* data);

		static bool HasComponent(EntityId entityId, ComponentId componentId);
		static bool HasComponent(Record* entityRecord, ComponentId componentId);

		static void* GetComponent(EntityId entityId, ComponentId componentId);
		static void* GetComponent(Record* entityRecord, ComponentId componentId);

		// Sets a new instance of the component data.
		static void SetComponent(EntityId entityId, ComponentId componentId, void* data);
		static void SetComponent(Record& entityRecord, ComponentId componentId, void* data);

		static unordered_map<EntityId, Record> entityIndex;
		static ArchetypeManager archetypeManager;

	private:
		static void edgeRemove(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);
		static void edgeAdd(Archetype* oldArchetype, Archetype* newArchetype, ComponentId componentId);

		static EntityId _entityIdState;
};
