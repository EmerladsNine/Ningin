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
		int row = 0;
		char* pointer = reinterpret_cast<char*>(scriptVecArchetype.second.archetype->components.GetEntityPointer(row));
		int entitySize = scriptVecArchetype.second.archetype->components.entitySize;
		int scriptVecPos = scriptVecArchetype.second.archetype->components.GetComponentPosition(typeid(ScriptVec));
		for (row = 0; row < scriptVecArchetype.second.archetype->size; row++)
		{
			ScriptVec& scriptVec = *reinterpret_cast<ScriptVec*>(pointer + scriptVecPos);
			for (Scriptable* script : scriptVec.scripts)
			{
				HandleScript(script, isLate, deltatime);
			}
			pointer += entitySize;
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
