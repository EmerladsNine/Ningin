#include "scriptable.h"
#include "../sceneSystem/components/ScriptVec.h"

void ScriptSystem(EntityManager* entityManager, Timer timer)
{
	ScriptUpdate(entityManager, false, timer);
}

void ScriptLateSystem(EntityManager* entityManager, Timer timer)
{
	ScriptUpdate(entityManager, true, timer);
}

void ScriptUpdate(EntityManager* entityManager, bool isLate, Timer timer)
{
	for (auto& scriptVecArchetype : entityManager->archetypeManager.componentIndex[typeid(ScriptVec)])
	{
		for (void* scriptsData : scriptVecArchetype.second.archetype
			->components[scriptVecArchetype.second.column])
		{
			ScriptVec* scripts = static_cast<ScriptVec*>(scriptsData);
			for (Scriptable* script : scripts->scripts)
			{
				HandleScript(script, isLate, timer);
			}
		}
	}
}

void HandleScript(Scriptable* script, bool isLate, Timer timer)
{
	if (script == nullptr) return;

	if (!script->HasStarted())
		script->Start();

	if (!isLate) script->Update(timer.GetDeltaTime());
	else script->LateUpdate(timer.GetDeltaTime());

}
