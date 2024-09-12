#pragma once

#include "ForceComputation.h"
#include "../../math/Vector3.h"
#include "../../math/Vector2.h"
#include "../../math/Math.h"
#include "forceType.h"
#include "../Axes.h"

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
