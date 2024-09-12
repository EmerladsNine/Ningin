#pragma once

#include "../../physics_manager/CollisionDetectionMode.h"
#include "../../physics_manager/PhysicsMaterial2D.h"
#include "../../physics_manager/InterpolationMode.h"
#include "../../physics_manager/force/force.h"
#include "../../physics_manager/SleepMode.h"
#include "../../physics_manager/bodyTypes.h"
#include "../../physics_manager/mask2.h"
#include "../../math/vector2.h"
#include "../../ningin.h"
#include <vector>

class RigidBody2D {
	public:
		RigidBody2D();
		~RigidBody2D();

		static void System(EntityManager* entityManager);

	private:
		float mass;
		float inertia;

		float linearDamping;
		float angularDamping;

		bool Simulated; // Forces are no longer applied
		bool useAutoInertia; // Calculates inertia using the mass

		BodyTypes bodyType;

		PhyscicsMaterial2D physcisMaterial;

		CollisionDetectionMode collisionDetectionMode;
		InterpolationMode interpolationMode;
		SleepMode sleepMode;

		std::vector<Force2D> forces;
		//std::vector<Torque2D> torques;

		Force2D constantForce; // Total positional forces applied during each frame
		//Torque2D constantTorque; // Total rotational forces applied during each frame

		Force2D gravity;

		Vector2 centerOfMass;

		Vector2 linearVelocity;
		Vector2 angularVelocity;

		Mask2 freezePosition;
		bool freezeRotation;

		void Update();
};
