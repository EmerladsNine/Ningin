#include "force.h"

Force2D::Force2D(float force_magnitude, float angle, Axes direction, ForceComputation computation, ForceType force_type)
	: force_type(force_type), angle(degrees_to_radians(angle)), computation(computation), direction(getDirectionVector(direction))
{
	Vector2 unnormalized_vector = Vector2(cos(this->angle), sin(this->angle));
	magnitude = Vector2_normalize(unnormalized_vector);
}

Force2D::Force2D(Vector2 force_magnitude, ForceType force_type, Axes direction, AppliedForceComputation computation)
	: magnitude(force_magnitude), force_type(force_type), computation(computation), direction(getDirectionVector(direction)), angle(-1) {}
