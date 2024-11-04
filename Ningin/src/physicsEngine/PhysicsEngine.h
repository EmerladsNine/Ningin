#pragma once
#include "../ecs/EntityManager.h"
class PhysicsEngine
{
public:
	PhysicsEngine();
	EntityManager physicsWorld;
};