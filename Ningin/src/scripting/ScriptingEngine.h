#pragma once

#include "ninginMono/MonoPaths.h"
#include "ninginMono/mono.h"
#include "ScriptLanguage.h"
#include "../sceneSystem/ecs/EntityManager.h"
#include <optional>
#include <string>

using namespace std;

class ScriptingEngine
{
	public:
		static Mono mono;

		template <typename T> static void RegisterComponent()
		{
			//Link To C#
			MonoType* managedType = ScriptingEngine::mono.GetComponentManagedType<T>();
			Mono::HasComponent[managedType] = [](EntityId entityId, EntityManager& entityManager) -> bool { return entityManager.HasComponent(entityId, typeid(T)); };
			Mono::GetComponent[managedType] = [](EntityId entityId, EntityManager& entityManager) -> void* { return entityManager.GetComponent(entityId, typeid(T)); };
		}

		static void Init(optional<MonoPaths> monoPath,bool debugMode);

		static Scriptable* GetScript(EntityId entityId, string scriptName, ScriptLanguage language);
};
