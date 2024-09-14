#pragma once

#include "../sceneSystem/ecs/EntityManager.h"

class Scriptable
{
	public:
		virtual bool HasStarted() = 0;

		virtual void Start() = 0;

		virtual void Update(float deltatime) = 0;
		virtual void LateUpdate(float deltatime) = 0;

		virtual void Destroy() = 0;
};

void ScriptSystem(EntityManager* entityManager, float deltaTime);

void ScriptLateSystem(EntityManager* entityManager, float deltaTime);

void ScriptUpdate(EntityManager* entityManager, bool isLate, float deltaTime);

void HandleScript(Scriptable* script, bool isLate, float deltaTime);
