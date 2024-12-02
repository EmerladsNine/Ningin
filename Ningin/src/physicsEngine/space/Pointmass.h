#pragma once

#include "../../math/vector3.h"
#include "Time.h"

namespace Ningin::Physics
{
	class Pointmass
	{
		public:
			Pointmass(float mass, float gravity, bool is_static);
			void Integrate(Time duration);
			void AddForce(const Vector3& force);
			void RemoveForce(const Vector3& force);
			const Vector3& GetVelocity();
			float gravity;
			bool is_static;
		private:
			void ClearAccumulator();
			float _InverseMass;
			Vector3 _ForceAccum;
			Vector3 _Position;
			Vector3 _Velocity;
			Vector3 _Acceleration;
	};
}
