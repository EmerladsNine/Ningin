#include "GravityForceGenerator.h"
#include "../space/Pointmass.h"

namespace Ningin::Physics
{

	GravityForceGenerator::GravityForceGenerator() : gravity(0)
	{
	}

	GravityForceGenerator::GravityForceGenerator(float gravity) : gravity(gravity)
	{
	}

	void GravityForceGenerator::System(float deltatime, ArchetypeManager& archetypeManager)
	{
		
	}

}
