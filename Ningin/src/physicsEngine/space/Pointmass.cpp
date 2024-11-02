#include "Pointmass.h"

Ningin::Physics::Pointmass::Pointmass(float mass, float gravity, DragForce dragForce, bool is_static) : _InverseMass(1 / mass), gravity(gravity), is_static(is_static) , dragForce(dragForce)
{}

void Ningin::Physics::Pointmass::Integrate(Time duration)
{
	//Update Linear Position.
	_Position += _Velocity * duration;

	//Update Acceleration by forces.
	Vector3 resultAcceleration = _Acceleration;
	resultAcceleration += _ForceAccum * _InverseMass;

	//Update Linear Velocity.
	_Velocity += resultAcceleration * duration;

	//Clear forces
	ClearAccumulator();
}

void Ningin::Physics::Pointmass::AddForce(const Vector3& force)
{
	_ForceAccum += force;
}

void Ningin::Physics::Pointmass::RemoveForce(const Vector3& force)
{
	_ForceAccum -= force;
}

const Vector3& Ningin::Physics::Pointmass::GetVelocity()
{
	return _Velocity;
}

void Ningin::Physics::Pointmass::ClearAccumulator()
{
	_ForceAccum = Vector3::ZERO;
}
