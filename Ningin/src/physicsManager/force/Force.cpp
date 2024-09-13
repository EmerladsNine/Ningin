#include "Force.h"

Force2D::Force2D(float force_magnitude, float angle, Axes direction, ForceComputation computation, ForceType force_type)
	: force_type(force_type), angle(DegreesToRadians(angle)), computation(computation), 
	direction(GetDirectionVector(direction))
{
	Vector2 unnormalized_vector = Vector2(cos(this->angle), sin(this->angle));
	Vector2 magnitude;

	Vector2Normalize(unnormalized_vector, magnitude);
}

Force2D::Force2D(Vector2 force_magnitude, ForceType force_type, Axes direction, AppliedForceComputation computation)
	: magnitude(force_magnitude), force_type(force_type), computation(computation),
	direction(GetDirectionVector(direction)), angle(-1) {}
