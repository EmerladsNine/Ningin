#include "vector3.h"
#include "math.h"
#include "vector2.h"

using namespace std;

// Static Constants Initialization
const Vector3 Vector3::UNIT_X = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ONE = Vector3(1.0f, 1.0f, 1.0f);

// ructors
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(Vector2& vec) : x(vec.x), y(vec.y), z(0.0f)
{
}

void Vector3_abs(Vector3& vec, Vector3& out)
{
	out.x = std::abs(vec.x);
	out.y = std::abs(vec.y);
	out.z = std::abs(vec.z);
}

void Vector3_squareRoot(Vector3& vec, Vector3& out)
{
	out.x = sqrt(vec.x);
	out.y = sqrt(vec.y);
	out.z = sqrt(vec.z);
}

void Vector3_add(Vector3& v1, Vector3& v2, Vector3& out)
{
	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	out.z = v1.z + v2.z;
}

float Vector3_magnitude(Vector3& vec)
{
	return sqrt(Vector3_dot(vec, vec));
}

Vector3 Vector3_normalize(Vector3& vec)
{
	float length = Vector3_magnitude(vec);
	return Vector3(vec.x / length, vec.y / length, vec.z/length);
}

float Vector3_dot(Vector3& v1, Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Vector3_distance(Vector3& v1, Vector3& v2)
{
	Vector3 vec = Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return Vector3_magnitude(vec);
}

float Vector3_distanceSquared(Vector3& v1, Vector3& v2)
{
	float distance = Vector3_distance(v1, v2);
	return distance * distance;
}

float Vector3_magnitudeSquared(Vector3& vec)
{
	return Vector3_dot(vec, vec);
}

void Vector3_max(Vector3& v1, Vector3& v2, Vector3& out)
{
	out = Vector3(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}

void Vector3_min(Vector3& v1, Vector3& v2, Vector3& out)
{
	out = Vector3(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}

void Vector3_clamp(Vector3& toClamp, Vector3& min, Vector3& max, Vector3& out)
{
	out.x = clamp(toClamp.x, min.x, max.x);
	out.y = clamp(toClamp.y, min.y, max.y);
	out.z = clamp(toClamp.z, min.z, max.z);
}

// Operator Overloads
Vector3 operator-(Vector3 vec)
{
	return Vector3(-vec.x, -vec.y, -vec.z);
}

Vector3 operator+(Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator-(Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator*(Vector3 vec, float a)
{
	return Vector3(vec.x * a, vec.y * a, vec.z * a);
}

Vector3 operator*(Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3 operator/(Vector3 vec, float a)
{
	return Vector3(vec.x / a, vec.y / a, vec.z / a);
}

Vector3 operator/(Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

bool operator==(Vector3 v1, Vector3 v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

bool operator!=(Vector3 v1, Vector3 v2)
{
	return !(v1 == v2);
}

bool operator<(Vector3 v1, Vector3 v2)
{
	return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z;
}

bool operator<=(Vector3 v1, Vector3 v2)
{
	return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z;
}

bool operator>(Vector3 v1, Vector3 v2)
{
	return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z;
}

bool operator>=(Vector3 v1, Vector3 v2)
{
	return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z;
}

string Vector3_toString(Vector3& vec)
{
	return format("Vector2 - x: {}, y: {}, z: {}", vec.x, vec.y, vec.z);
}

Vector3 fromVector2(Vector2& vec)
{
	return Vector3(vec.x, vec.y);
}