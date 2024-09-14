#include "scriptable.h"
#include "../sceneSystem/components/ScriptVec.h"

void ScriptSystem(EntityManager* entityManager, float deltaTime)
{
	ScriptUpdate(entityManager, false, deltaTime);
}

void ScriptLateSystem(EntityManager* entityManager, float deltaTime)
{
	ScriptUpdate(entityManager, true, deltaTime);
}

void ScriptUpdate(EntityManager* entityManager, bool isLate, float deltaTime)
{
	for (auto& scriptVecArchetype : entityManager->archetypeManager.componentIndex[typeid(ScriptVec)])
	{
		for (void* scriptData : scriptVecArchetype.second.archetype
			->components[scriptVecArchetype.second.column])
		{
			Scriptable* script = static_cast<Scriptable*>(scriptData);
			HandleScript(script, isLate, deltaTime);
		}
	}
}

void HandleScript(Scriptable* script, bool isLate, float deltaTime)
{
	if (script == nullptr) return;

	if (!script->HasStarted())
		script->Start();

	if (!isLate) script->Update(deltaTime);
	else script->LateUpdate(deltaTime);

}
