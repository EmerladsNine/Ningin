#include "scriptable.h"
#include "../sceneSystem/ecs/EntityManager.h"
#include "../sceneSystem/components/ScriptVec.h"

void ScriptSystem(Timer timer)
{
	ScriptUpdate(false, timer);
}

void ScriptLateSystem(Timer timer)
{
	ScriptUpdate(true, timer);
}

void ScriptUpdate(bool isLate, Timer timer)
{
	for (auto& scriptVecArchetype : EntityManager::archetypeManager.componentIndex[typeid(ScriptVec)])
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
