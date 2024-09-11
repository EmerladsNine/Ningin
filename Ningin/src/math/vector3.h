#pragma once

#include <string>

class Vector2;

class Vector3
{
public:
	float x, y, z;

	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;
	static const Vector3 ZERO;
	static const Vector3 ONE;

	// Constructors
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	Vector3(Vector2& vec);
};

void Vector3_abs(Vector3& vec, Vector3& out);

void Vector3_squareRoot(Vector3& vec, Vector3& out);

void Vector3_add(Vector3& v1, Vector3& v2, Vector3& out);

float Vector3_magnitude(Vector3& vec);

Vector3 Vector3_normalize(Vector3& vec);

float Vector3_dot(Vector3& v1, Vector3& v2);

float Vector3_distance(Vector3& v1, Vector3& v2);

float Vector3_distanceSquared(Vector3& v1, Vector3& v2);

float Vector3_magnitudeSquared(Vector3& vec);

void Vector3_max(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3_min(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3_clamp(Vector3& toClamp, Vector3& min, Vector3& max, Vector3& out);

Vector3 operator-(Vector3 vec);

Vector3 operator+(Vector3 v1, Vector3 v2);

Vector3 operator-(Vector3 v1, Vector3 v2);

Vector3 operator*(Vector3 vec, float a);

Vector3 operator*(Vector3 v1, Vector3 v2);

Vector3 operator/(Vector3 vec, float a);

Vector3 operator/(Vector3 v1, Vector3 v2);

bool operator==(Vector3 v1, Vector3 v2);

bool operator!=(Vector3 v1, Vector3 v2);

bool operator<(Vector3 v1, Vector3 v2);

bool operator<=(Vector3 v1, Vector3 v2);

bool operator>(Vector3 v1, Vector3 v2);

bool operator>=(Vector3 v1, Vector3 v2);

std::string Vector3_toString(Vector3& vec);

Vector3 fromVector2(Vector2& vec);
