#pragma once

#include "force_computation.h"
#include "../math/vector3.h"
#include "../math/vector2.h"
#include "../math/math.h"
#include "force_type.h"
#include "axes.h"

struct Force2D {
	private:
		Vector3 direction;
		Vector2 magnitude;

		ForceComputation computation;
		ForceType force_type;

		float angle;

	public:
		Force2D(float force_magnitude, float angle, Axes direction, ForceComputation computation, ForceType force_type);
		Force2D(Vector2 force_magnitude, ForceType force_type, Axes direction, AppliedForceComputation computation);
};
