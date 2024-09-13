#pragma once

#include "../sceneSystem/ecs/EntityManager.h"

class Scriptable
{
	public:
		virtual bool IsStarted() = 0;

		virtual void Start() = 0;

		virtual void Update(float deltatime) = 0;
		virtual void LateUpdate(float deltatime) = 0;

		virtual void Destroy() = 0;
};

void ScriptSystem(float deltatime, EntityManager* entityManager);

void ScriptLateSystem(float deltatime, EntityManager* entityManager);
