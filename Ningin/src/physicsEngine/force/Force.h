#pragma once

#include "ForceComputation.h"
#include "../../math/Vector3.h"
#include "../../math/Vector2.h"
#include "../../math/Math.h"
#include "forceType.h"
#include "../Axes.h"

struct Force2D {
	private:
		Vector3 _direction;
		Vector2 _magnitude;
		Vector2 _normalizedMagnitude;

		ForceComputation _computation;
		ForceType _forceType;

		float _angle;

	public:
		Force2D(float forceMagnitude, float angle, Axes direction, ForceComputation computation,
			ForceType forceType);

		Force2D(Vector2 forceMagnitude, ForceType forceType, Axes direction,
			AppliedForceComputation computation);
};
