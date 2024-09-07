#include "Vector3.h"
#include "Vector2.h"
#include "math.h"

// Static Constants Initialization
const Vector3 Vector3::UNIT_X = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ONE = Vector3(1.0f, 1.0f, 1.0f);

// Constructors
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(const Vector2& vec) : x(vec.x), y(vec.y), z(0.0f) {}

// Methods
void Vector3::abs(Vector3& out) const {
	out.x = std::abs(x);
	out.y = std::abs(y);
	out.z = std::abs(z);
}

void Vector3::squareRoot(Vector3& out) const {
	out.x = std::sqrt(x);
	out.y = std::sqrt(y);
	out.z = std::sqrt(z);
}

void Vector3::add(const Vector3& other, Vector3& out) const {
	out.x = x + other.x;
	out.y = y + other.y;
	out.z = z + other.z;
}

float Vector3::distance(const Vector3& other) const {
	return Vector3(x - other.x, y - other.y, z - other.z).magnitude();
}

float Vector3::distanceSquared(const Vector3& other) const {
	float distance = this->distance(other);
	return distance * distance;
}

float Vector3::dot(const Vector3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

float Vector3::magnitude() const {
	return std::sqrt(this->dot(*this));
}

float Vector3::magnitudeSquared() const {
	return this->dot(*this);
}

void Vector3::max(const Vector3& v1, const Vector3& v2, Vector3& out) {
	out.x = std::fmax(v1.x, v2.x);
	out.y = std::fmax(v1.y, v2.y);
	out.z = std::fmax(v1.z, v2.z);
}

void Vector3::min(const Vector3& v1, const Vector3& v2, Vector3& out) {
	out.x = std::fmin(v1.x, v2.x);
	out.y = std::fmin(v1.y, v2.y);
	out.z = std::fmin(v1.z, v2.z);
}

void Vector3::clamp(const Vector3& toClamp, const Vector3& min, const Vector3& max, Vector3& out) {
	out.x = math::clamp(toClamp.x, min.x, max.x);
	out.y = math::clamp(toClamp.y, min.y, max.y);
	out.z = math::clamp(toClamp.z, min.z, max.z);
}

// Operator Overloads
Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float a) const {
	return Vector3(x * a, y * a, z * a);
}

Vector3 Vector3::operator*(const Vector3& other) const {
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator/(float a) const {
	return Vector3(x / a, y / a, z / a);
}

Vector3 Vector3::operator/(const Vector3& other) const {
	return Vector3(x / other.x, y / other.y, z / other.z);
}

bool Vector3::operator==(const Vector3& other) const {
	return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!=(const Vector3& other) const {
	return !(*this == other);
}

bool Vector3::operator<(const Vector3& other) const {
	return x < other.x && y < other.y && z < other.z;
}

bool Vector3::operator<=(const Vector3& other) const {
	return x <= other.x && y <= other.y && z <= other.z;
}

bool Vector3::operator>(const Vector3& other) const {
	return x > other.x && y > other.y && z > other.z;
}

bool Vector3::operator>=(const Vector3& other) const {
	return x >= other.x && y >= other.y && z >= other.z;
}

// Debugging
std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
	os << "Vector3 - x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
	return os;
}