#include "vector2.h"
#include "math.h"
#include "vector3.h"

using namespace std;

// Constants
const Vector2 UNIT_X = Vector2(1.0f, 0.0f);
const Vector2 UNIT_Y = Vector2(0.0f, 1.0f);
const Vector2 ZERO = Vector2(0.0f, 0.0f);
const Vector2 ONE = Vector2(1.0f, 1.0f);

void Vector2_abs(Vector2 vec, Vector2& out)
{
	out = Vector2(std::fabs(vec.x), std::fabs(vec.y));
}

void Vector2_squareRoot(Vector2 vec, Vector2& out)
{
	out = Vector2(std::sqrt(vec.x), std::sqrt(vec.y));
}

void Vector2_add(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(v1.x + v2.x, v1.y + v2.y);
}

float Vector2_dot(Vector2& v1, Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2_magnitude(Vector2& vec)
{
	return sqrt(Vector2_dot(vec, vec));
}

float Vector2_distance(Vector2& v1, Vector2& v2)
{
	Vector2 vec = Vector2(v1.x - v2.x, v1.y - v2.y);
	return Vector2_magnitude(vec);
}

float Vector2_distanceSquared(Vector2& v1, Vector2& v2)
{
	float dist = Vector2_distance(v1, v2);
	return dist * dist;
}

float Vector2_magnitudeSquared(Vector2& vec)
{
	return Vector2_dot(vec, vec);
}

void Vector2_max(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(max(v1.x, v2.x), max(v1.y, v2.y));
}

void Vector2_min(Vector2& v1, Vector2& v2, Vector2& out)
{
	out = Vector2(min(v1.x, v2.x), min(v1.y, v2.y));
}

void Vector2_clamp(Vector2& vec_to_clamp, Vector2& min, Vector2& max, Vector2& out)
{
	out = Vector2(clamp(vec_to_clamp.x, min.x, max.x), clamp(vec_to_clamp.y, min.y, max.y));
}

Vector2 operator-(Vector2 vec)
{
	return Vector2(-vec.x, -vec.y);
}

Vector2 operator+(Vector2 v1, Vector2 v2)
{
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 operator-(Vector2 v1, Vector2 v2)
{
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2 operator*(Vector2 vec, float a)
{
	return Vector2(vec.x * a, vec.y * a);
}

Vector2 operator*(Vector2 v1, Vector2 v2)
{
	return Vector2(v1.x * v2.x, v1.y * v2.y);
}

Vector2 operator/(Vector2 v1, Vector2 v2)
{
	return Vector2(v1.x / v2.x, v1.y / v2.y);
}

Vector2 operator/(Vector2 vec, float a)
{
	return Vector2(vec.x / a, vec.y / a);
}

bool operator==(Vector2 v1, Vector2 v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(Vector2 v1, Vector2 v2)
{
	return !(v1 == v2);
}

bool operator<(Vector2& v1, Vector2 v2)
{
	return v1.x < v2.x && v1.y < v2.y;
}

bool operator>(Vector2& v1, Vector2 v2)
{
	return v1.x > v2.x && v1.y > v2.y;
}

string Vector2_toString(Vector2 vec)
{
	return format("Vector2 - x: {}, y: {}", vec.x, vec.y);
}

Vector2 fromVector3(Vector3& vec)
{
	return Vector2(vec.x, vec.y);
}