#pragma once

#include "../../physicsManager/CollisionDetectionMode.h"
#include "../../physicsManager/PhysicsMaterial2D.h"
#include "../../physicsManager/InterpolationMode.h"
#include "../../physicsManager/force/force.h"
#include "../../physicsManager/SleepMode.h"
#include "../../physicsManager/bodyTypes.h"
#include "../../physicsManager/mask2.h"
#include "../../math/vector2.h"
#include "../../ningin.h"
#include <vector>

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
