#include "scriptable.h"
#include "../scene_system/components/ScriptVec.h"

void ScriptSystem(float deltatime, EntityManager* entityManager)
{
	for (auto& scriptVecArchetype : entityManager->archetypeManager.componentIndex[typeid(ScriptVec)])
	{
		for (void* scriptData : scriptVecArchetype.second.archetype->components[scriptVecArchetype.second.column])
		{
			Scriptable* script = static_cast<Scriptable*>(scriptData);
			if (script != nullptr)
			{
				if (!script->IsStarted())
				{
					script->Start();
				}
				script->Update(deltatime);
			}
		}
	}
}

void ScriptLateSystem(float deltatime, EntityManager* entityManager)
{
	for (auto& scriptVecArchetype : entityManager->archetypeManager.componentIndex[typeid(ScriptVec)])
	{
		for (void* scriptData : scriptVecArchetype.second.archetype->components[scriptVecArchetype.second.column])
		{
			Scriptable* script = static_cast<Scriptable*>(scriptData);
			if (script != nullptr)
			{
				if (script->IsStarted())
				{
					script->LateUpdate(deltatime);
				}
			}
		}
	}
}