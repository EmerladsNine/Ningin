#include "Vector2.h"
#include "Math.h"
#include "Vector3.h"

// Constants
const Vector2 UNIT_X = Vector2(1.0f, 0.0f);
const Vector2 UNIT_Y = Vector2(0.0f, 1.0f);
const Vector2 ZERO = Vector2(0.0f, 0.0f);
const Vector2 ONE = Vector2(1.0f, 1.0f);

void Vector2Abs(Vector2& vec, Vector2& out)
{
	out = Vector2(std::fabs(vec.x), std::fabs(vec.y));
}

void Vector2Inverse(Vector2& vec, Vector2& out)
{
	out = Vector2(1 / vec.x, 1 / vec.y);
}

void Vector2SquareRoot(Vector2& vec, Vector2& out)
{
	out = Vector2(std::sqrt(vec.x), std::sqrt(vec.y));
}

void Vector2Add(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(v1.x + v2.x, v1.y + v2.y);
}

float Vector2Dot(Vector2& v1, Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2Magnitude(Vector2& vec)
{
	return sqrt(Vector2Dot(vec, vec));
}

void Vector2Normalize(Vector2& vec, Vector2& out)
{
	float length = Vector2Magnitude(vec);
	out = Vector2(vec.x/length, vec.y/length);
}

float Vector2Distance(Vector2& v1, Vector2& v2)
{
	Vector2 vec = Vector2(v1.x - v2.x, v1.y - v2.y);
	return Vector2Magnitude(vec);
}

float Vector2DistanceSquared(Vector2& v1, Vector2& v2)
{
	float dist = Vector2Distance(v1, v2);
	return dist * dist;
}

float Vector2MagnitudeSquared(Vector2& vec)
{
	return Vector2Dot(vec, vec);
}

void Vector2Max(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(max(v1.x, v2.x), max(v1.y, v2.y));
}

void Vector2Min(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(min(v1.x, v2.x), min(v1.y, v2.y));
}

void Vector2Clamp(Vector2& vec_toClamp, Vector2& min, Vector2& max, Vector2& out)
{
	out = Vector2(Clamp(vec_toClamp.x, min.x, max.x), Clamp(vec_toClamp.y, min.y, max.y));
}

void Vector2Negate(Vector2& vec, Vector2& out)
{
	out = Vector2(-vec.x, -vec.y);
}

void Vector2Subtract(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(v1.x - v2.x, v1.y - v2.y);
}

void Vector2MultiplyByFloat(Vector2& vec, float a, Vector2& out)
{
	out = Vector2(vec.x * a, vec.y * a);
}

void Vector2Multiply(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(v1.x * v2.x, v1.y * v2.y);
}

void Vector2Divide(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(v1.x / v2.x, v1.y / v2.y);
}

void Vector2DivideByFloat(Vector2& vec, float a, Vector2& out)
{
	out = Vector2(vec.x / a, vec.y / a);
}

bool Vector2Equals(Vector2& v1, Vector2& v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

bool Vector2NotEqual(Vector2& v1, Vector2& v2)
{
	return !(Vector2Equals(v1, v2));
}

bool Vector2L(Vector2& v1, Vector2& v2)
{
	return v1.x < v2.x && v1.y < v2.y;
}

bool Vector2G(Vector2& v1, Vector2& v2)
{
	return v1.x > v2.x && v1.y > v2.y;
}

bool Vector2LE(Vector2& v1, Vector2& v2)
{
	return v1.x <= v2.x && v1.y <= v2.y;
}

bool Vector2GE(Vector2& v1, Vector2& v2)
{
	return v1.x >= v2.x && v1.y >= v2.y;
}

void Vector2ToString(Vector2& vec, string& out)
{
	out = format("Vector2 - x: {}, y: {}", vec.x, vec.y);
}

void Vector2FromVector3(Vector3& vec, Vector2& out)
{
	out = Vector2(vec.x, vec.y);
}