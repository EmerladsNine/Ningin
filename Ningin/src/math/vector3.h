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
		static const Vector3 UNIT_XY;
		static const Vector3 UNIT_XZ;
		static const Vector3 UNIT_YZ;
		static const Vector3 ZERO;
		static const Vector3 ONE;

		// Constructors
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		Vector3(Vector2& vec);
};

void Vector3Abs(Vector3& vec, Vector3& out);

void Vector3SquareRoot(Vector3& vec, Vector3& out);

void Vector3Add(Vector3& v1, Vector3& v2, Vector3& out);

float Vector3Magnitude(Vector3& vec);

Vector3 Vector3Normalize(Vector3& vec);

float Vector3Dot(Vector3& v1, Vector3& v2);

float Vector3Distance(Vector3& v1, Vector3& v2);

float Vector3DistanceSquared(Vector3& v1, Vector3& v2);

float Vector3MagnitudeSquared(Vector3& vec);

void Vector3Max(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3Min(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3Clamp(Vector3& vecToClamp, Vector3& min, Vector3& max, Vector3& out);

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

std::string Vector3ToString(Vector3& vec);

Vector3 FromVector2(Vector2& vec);
