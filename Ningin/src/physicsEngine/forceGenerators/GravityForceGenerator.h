#pragma once
#include "../../ecs/ArchetypeManager.h"
#include "../space/Pointmass.h"
namespace Ningin::Physics
{
	class GravityForceGenerator
	{
	public:
		GravityForceGenerator();
		GravityForceGenerator(float gravity);
		float gravity;
		static void Update(Pointmass* pointmass, float gravity);
		static void System(float deltatime, ArchetypeManager& archetypeManager);
	private:

	};
}