#include "ForceGenerator.h"

void Ningin::Physics::ForceGenerator::updateForces(Pointmass* pointmass, Time duration)
{
	//Add Gravity Force
	if (!pointmass->is_static)
	{
		Vector3 test(0, -pointmass->gravity, 0);
		pointmass->AddForce(test);
	}
}