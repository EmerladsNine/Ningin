#include "Vector3.h"
#include "Math.h"
#include "Vector2.h"

// Static Constants Initialization
const Vector3 Vector3::UNIT_X = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::UNIT_XY = Vector3(1.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_XZ = Vector3(1.0f, 0.0f, 1.0f);
const Vector3 Vector3::UNIT_YZ = Vector3(0.0f, 1.0f, 1.0f);
const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ONE = Vector3(1.0f, 1.0f, 1.0f);

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(Vector2& vec) : x(vec.x), y(vec.y), z(0.0f) {}

void Vector3Abs(Vector3& vec, Vector3& out)
{
	out.x = std::abs(vec.x);
	out.y = std::abs(vec.y);
	out.z = std::abs(vec.z);
}

void Vector3SquareRoot(Vector3& vec, Vector3& out)
{
	out.x = sqrt(vec.x);
	out.y = sqrt(vec.y);
	out.z = sqrt(vec.z);
}

void Vector3Add(Vector3& v1, Vector3& v2, Vector3& out)
{
	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	out.z = v1.z + v2.z;
}

float Vector3Magnitude(Vector3& vec)
{
	return sqrt(Vector3Dot(vec, vec));
}

void Vector3Normalize(Vector3& vec, Vector3& out)
{
	float length = Vector3Magnitude(vec);
	out = Vector3(vec.x / length, vec.y / length, vec.z/length);
}

float Vector3Dot(Vector3& v1, Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Vector3Distance(Vector3& v1, Vector3& v2)
{
	Vector3 vec = Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return Vector3Magnitude(vec);
}

float Vector3DistanceSquared(Vector3& v1, Vector3& v2)
{
	float distance = Vector3Distance(v1, v2);
	return distance * distance;
}

float Vector3MagnitudeSquared(Vector3& vec)
{
	return Vector3Dot(vec, vec);
}

void Vector3Max(Vector3& v1, Vector3& v2, Vector3& out)
{
	out = Vector3(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}

void Vector3Min(Vector3& v1, Vector3& v2, Vector3& out)
{
	out = Vector3(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}

void Vector3Clamp(Vector3& vecToClamp, Vector3& min, Vector3& max, Vector3& out)
{
	out.x = Clamp(vecToClamp.x, min.x, max.x);
	out.y = Clamp(vecToClamp.y, min.y, max.y);
	out.z = Clamp(vecToClamp.z, min.z, max.z);
}

void Vector3Negate(Vector3& vec, Vector3& out) {
	out = Vector3(-vec.x, -vec.y, -vec.z);
}

void Vector3Subtract(Vector3& v1, Vector3& v2, Vector3& out){
	out = Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

void Vector3MultiplyByFloat(Vector3& vec, float a, Vector3& out){
	out = Vector3(vec.x * a, vec.y * a, vec.z * a);
}

void Vector3Multiply(Vector3& v1, Vector3& v2, Vector3& out){
	out = Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

void Vector3Divide(Vector3& v1, Vector3& v2, Vector3& out){
	out = Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

void Vector3DivideByFloat(Vector3& vec, float a, Vector3& out){
	out = Vector3(vec.x / a, vec.y / a, vec.z / a);

}

bool Vector3Equals(Vector3& v1, Vector3& v2){
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

bool Vector3NotEqual(Vector3& v1, Vector3& v2){
	return !(Vector3Equals(v1, v2));
}

bool Vector3L(Vector3& v1, Vector3& v2){
	return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z;
}

bool Vector3LE(Vector3& v1, Vector3& v2){
	return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z;

}

bool Vector3G(Vector3& v1, Vector3& v2){
	return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z;
}

bool Vector3GE(Vector3& v1, Vector3& v2){
	return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z;
}

void Vector3ToString(Vector3& vec, string& out)
{
	out = format("Vector2 - x: {}, y: {}, z: {}", vec.x, vec.y, vec.z);
}

void Vector3FromVector2(Vector2& vec, Vector3& out)
{
	out = Vector3(vec.x, vec.y);
}