#include "Pointmass.h"

Ningin::Physics::Pointmass::Pointmass(float mass) : _InverseMass(1/mass)
{
}

void Ningin::Physics::Pointmass::Integrate(Time duration)
{
	//Update Linear Position.
	_Position += _Velocity * duration;

	//Update Acceleration by forces.
	Vector3 resultAcceleration = _Acceleration;
	resultAcceleration += forceAccum * _InverseMass;

	//Update Linear Velocity.
	_Velocity += resultAcceleration * duration;
}
