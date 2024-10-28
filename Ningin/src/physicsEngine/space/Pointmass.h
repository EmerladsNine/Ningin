#pragma once
#include "../../math/vector3.h"
#include "Time.h"

namespace Ningin::Physics
{
	class Pointmass
	{
	public:
		Pointmass(float mass);
		void Integrate(Time duration);
	private:
		float _InverseMass;
		Vector3 forceAccum;
		Vector3 _Position;
		Vector3 _Velocity;
		Vector3 _Acceleration;
	};
}