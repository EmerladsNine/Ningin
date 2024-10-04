#pragma once
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

void ScriptSystem(float deltatime);

void ScriptLateSystem(float deltatime);

void ScriptUpdate(bool isLate, float deltatime);

void HandleScript(Scriptable* script, bool isLate, float deltatime);
