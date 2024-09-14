#include "Force.h"

Force2D::Force2D(float forceMagnitude, float angle, Axes direction, ForceComputation computation,
	ForceType forceType) : _forceType(forceType), _angle(DegreesToRadians(angle)), _computation(computation), 
	_direction(GetDirectionVector(direction))
{
	Vector2 unnormalizedVector = Vector2(cos(this->_angle), sin(this->_angle));

	Vector2Normalize(unnormalizedVector, _normalizedMagnitude);
	Vector2MultiplyByFloat(_normalizedMagnitude, forceMagnitude, _magnitude);
}

Force2D::Force2D(Vector2 forceMagnitude, ForceType forceType, Axes direction,
	AppliedForceComputation computation)
	: _magnitude(forceMagnitude), _forceType(forceType), _computation(computation),
	_direction(GetDirectionVector(direction)), _angle(-1) {}
