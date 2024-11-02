#pragma once
#include "../utils/Timer.h"
#include "../ecs/ArchetypeManager.h"

class Scriptable
{
	public:
		virtual bool HasStarted() = 0;

		virtual void Start() = 0;

		virtual void Update(float deltatime) = 0;
		virtual void LateUpdate(float deltatime) = 0;

		virtual void Destroy() = 0;
};

void ScriptSystem(float deltatime, ArchetypeManager& archetypeManager);

void ScriptLateSystem(float deltatime, ArchetypeManager& archetypeManager);

void ScriptUpdate(bool isLate, float deltatime, ArchetypeManager& archetypeManager);

void HandleScript(Scriptable* script, bool isLate, float deltatime);
