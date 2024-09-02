#include "Vector2.h"
#include "Vector3.h"
#include "math.h"

// Constants
const Vector2 Vector2::UNIT_X = Vector2(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y = Vector2(0.0f, 1.0f);
const Vector2 Vector2::ZERO = Vector2(0.0f, 0.0f);
const Vector2 Vector2::ONE = Vector2(1.0f, 1.0f);

void Vector2::abs(Vector2& out) const {
    out = Vector2(std::fabs(x), std::fabs(y));
}

void Vector2::squareRoot(Vector2& out) const {
    out = Vector2(std::sqrt(x), std::sqrt(y));
}

void Vector2::add(const Vector2& other, Vector2& out) const {
    out = Vector2(x + other.x, y + other.y);
}

float Vector2::distance(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y).magnitude();
}

float Vector2::distanceSquared(const Vector2& other) const {
    float dist = distance(other);
    return dist * dist;
}

float Vector2::dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

float Vector2::magnitude() const {
    return std::sqrt(dot(*this));
}

float Vector2::magnitudeSquared() const {
    return dot(*this);
}

void Vector2::max(const Vector2& v1, const Vector2& v2, Vector2& out) {
    out = Vector2(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
}

void Vector2::min(const Vector2& v1, const Vector2& v2, Vector2& out) {
    out = Vector2(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
}

void Vector2::clamp(const Vector2& vec_to_clamp, const Vector2& min, const Vector2& max, Vector2& out) {
    out = Vector2(
        math::clamp(vec_to_clamp.x, min.x, max.x),
        math::clamp(vec_to_clamp.y, min.y, max.y)
    );
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float a) const {
    return Vector2(x * a, y * a);
}

Vector2 Vector2::operator*(const Vector2& other) const {
    return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator/(const Vector2& other) const {
    return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator/(float a) const {
    return Vector2(x / a, y / a);
}

bool Vector2::operator==(const Vector2& other) const {
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const {
    return !(*this == other);
}

bool Vector2::operator<(const Vector2& other) const {
    return x < other.x && y < other.y;
}

bool Vector2::operator>(const Vector2& other) const {
    return x > other.x && y > other.y;
}

std::string Vector2::toString() const {
    return "Vector2 - x: " + std::to_string(x) + ", y: " + std::to_string(y);
}

Vector2 Vector2::fromVector3(const Vector3& vec) {
    return Vector2(vec.x, vec.y);
}
