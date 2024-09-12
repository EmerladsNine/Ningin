#include "vector2.h"
#include "math.h"
#include "vector3.h"

using namespace std;

// Constants
const Vector2 UNIT_X = Vector2(1.0f, 0.0f);
const Vector2 UNIT_Y = Vector2(0.0f, 1.0f);
const Vector2 ZERO = Vector2(0.0f, 0.0f);
const Vector2 ONE = Vector2(1.0f, 1.0f);

void Vector2Abs(Vector2 vec, Vector2& out)
{
	out = Vector2(std::fabs(vec.x), std::fabs(vec.y));
}

void Vector2SquareRoot(Vector2 vec, Vector2& out)
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

Vector2 Vector2Normalize(Vector2& vec)
{
	float length = Vector2Magnitude(vec);
	return Vector2(vec.x/length, vec.y/length);
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

string Vector2ToString(Vector2 vec)
{
	return format("Vector2 - x: {}, y: {}", vec.x, vec.y);
}

Vector2 FromVector3(Vector3& vec)
{
	return Vector2(vec.x, vec.y);
}