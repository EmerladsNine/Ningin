#pragma once

#include "../sceneSystem/ecs/EntityManager.h"
#include "../utils/Timer.h"

class Scriptable
{
	public:
		virtual bool HasStarted() = 0;

		virtual void Start() = 0;

		virtual void Update(float deltatime) = 0;
		virtual void LateUpdate(float deltatime) = 0;

		virtual void Destroy() = 0;
};

void ScriptSystem(Timer timer);

void ScriptLateSystem(Timer timer);

void ScriptUpdate(bool isLate, Timer timer);

void HandleScript(Scriptable* script, bool isLate, Timer timer);
