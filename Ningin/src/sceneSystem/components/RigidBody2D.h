#pragma once

#include "../../physicsEngine/CollisionDetectionMode.h"
#include "../../physicsEngine/PhysicsMaterial2D.h"
#include "../../physicsEngine/InterpolationMode.h"
#include "../../physicsEngine/force/force.h"
#include "../../physicsEngine/SleepMode.h"
#include "../../physicsEngine/bodyTypes.h"
#include "../../physicsEngine/mask2.h"
#include "../../math/vector2.h"
#include "../../ningin.h"
#include <vector>

namespace Ningin
{
	using namespace Physics;

	namespace Components
	{
		class RigidBody2D {
		public:
			RigidBody2D();
			~RigidBody2D();

			static void System(EntityManager* entityManager);

		private:
			float _mass;
			float _inertia;

			float _linearDamping;
			float _angularDamping;

			bool _simulated; // Forces are no longer applied
			bool _useAutoInertia; // Calculates inertia using the mass

			BodyTypes _bodyType;

			PhyscicsMaterial2D _physcisMaterial;

			CollisionDetectionMode _collisionDetectionMode;
			InterpolationMode _interpolationMode;
			SleepMode _sleepMode;

			std::vector<Force2D> _forces;
			//std::vector<Torque2D> _torques;

			Force2D _constantForce; // Total positional forces applied during each frame
			//Torque2D _constantTorque; // Total rotational forces applied during each frame

			Force2D _gravity;

			Vector2 _centerOfMass;

			Vector2 _linearVelocity;
			Vector2 _angularVelocity;

			Mask2 _freezePosition;
			bool _freezeRotation;

			void Update();
		};
	}
}
