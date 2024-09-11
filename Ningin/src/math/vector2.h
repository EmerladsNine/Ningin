#pragma once

#include <format>

class Vector3; // Forward declaration

class Vector2
{
public:
	float x, y;

	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
	static const Vector2 ZERO;
	static const Vector2 ONE;

	Vector2() : x(0), y(0)
	{
	}
	Vector2(float x, float y) : x(x), y(y)
	{
	}
};

void Vector2_abs(Vector2 vec, Vector2& out);

void Vector2_squareRoot(Vector2 vec, Vector2& out);

void Vector2_add(Vector2& v1, Vector2& v2, Vector2& out);

float Vector2_dot(Vector2& v1, Vector2& v2);

float Vector2_magnitude(Vector2& vec);

Vector2 Vector2_normalize(Vector2& vec);

float Vector2_distance(Vector2& v1, Vector2& v2);

float Vector2_distanceSquared(Vector2& v1, Vector2& v2);

float Vector2_magnitudeSquared(Vector2& vec);

void Vector2_max(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2_min(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2_clamp(Vector2& vec_to_clamp, Vector2& min, Vector2& max, Vector2& out);

Vector2 operator-(Vector2 vec);

Vector2 operator+(Vector2 v1, Vector2 v2);

Vector2 operator-(Vector2 v1, Vector2 v2);

Vector2 operator*(Vector2 vec, float a);

Vector2 operator*(Vector2 v1, Vector2 v2);

Vector2 operator/(Vector2 v1, Vector2 v2);

Vector2 operator/(Vector2 vec, float a);

bool operator==(Vector2 v1, Vector2 v2);

bool operator!=(Vector2 v1, Vector2 v2);

bool operator<(Vector2& v1, Vector2 v2);

bool operator>(Vector2& v1, Vector2 v2);

std::string Vector2_toString(Vector2 vec);

Vector2 fromVector3(Vector3& vec);
