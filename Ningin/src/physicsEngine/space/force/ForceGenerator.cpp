#include "ForceGenerator.h"

void Ningin::Physics::ForceGenerator::updateForces(Pointmass* pointmass, Time duration)
{
	if (!pointmass->is_static)
	{
		//Add Gravity Force
		Vector3 test(0, -pointmass->gravity, 0);
		pointmass->AddForce(test);

		//Add Drag Force
		const Vector3& velocity = pointmass->GetVelocity();
		float dragCoeff = velocity.Magnitude();
		dragCoeff = pointmass->dragForce.k1 * dragCoeff + pointmass->dragForce.k2 * dragCoeff * dragCoeff;
		Vector3& force = velocity.Normalize();
		force *= -dragCoeff;
		pointmass->AddForce(force);
	}
}