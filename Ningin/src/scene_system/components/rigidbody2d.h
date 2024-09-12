#pragma once

#include "../../physics_manager/force.h"
#include "../../physics_manager/mask2.h"
#include "../../physics_manager/InterpolationMode.h"
#include "../../physics_manager/CollisionDetectionMode.h"
#include "../../physics_manager/SleepMode.h"
#include "../../physics_manager/bodyTypes.h"
#include "../../physics_manager/physics_material2d.h"
#include "../../math/vector2.h"

class RigidBody2D {
	public:
		RigidBody2D();
		~RigidBody2D();

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

		Force2D constantForce; // Total positional forces applied during each frame
		//Torque constantTorque; // Total rotational forces applied during each frame

		Force2D gravity;

		Vector2 centerOfMass;

		Vector2 linearVelocity;
		Vector2 angularVelocity;

		Mask2 FreezePosition;
		bool FreezeRotation;

		void update();
};
