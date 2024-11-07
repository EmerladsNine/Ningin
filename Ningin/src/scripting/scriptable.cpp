#include "scriptable.h"
#include "../ecs/EntityManager.h"
#include "../sceneSystem/components/ScriptVec.h"

void ScriptSystem(float deltatime, ArchetypeManager& archetypeManager)
{
	ScriptUpdate(false, deltatime, archetypeManager);
}

void ScriptLateSystem(float deltatime, ArchetypeManager& archetypeManager)
{
	ScriptUpdate(true, deltatime, archetypeManager);
}

void ScriptUpdate(bool isLate, float deltatime, ArchetypeManager& archetypeManager)
{
	for (auto& scriptVecArchetype : archetypeManager.componentIndex[typeid(ScriptVec)])
	{
		std::vector<ScriptVec>& scriptVecVec = *static_cast<std::vector<ScriptVec>*>(scriptVecArchetype.second.archetype->components[typeid(ScriptVec)]);
		for (auto& scriptVec : scriptVecVec)
		{
			for (Scriptable* script : scriptVec.scripts)
			{
				HandleScript(script, isLate, deltatime);
			}
		}
	}
}

void HandleScript(Scriptable* script, bool isLate, float deltatime)
{
	if (script == nullptr) return;

	if (!script->HasStarted())
		script->Start();

	if (!isLate) script->Update(deltatime);
	else script->LateUpdate(deltatime);

}
