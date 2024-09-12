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

void Vector2Abs(Vector2 vec, Vector2& out);

void Vector2SquareRoot(Vector2 vec, Vector2& out);

void Vector2Add(Vector2& v1, Vector2& v2, Vector2& out);

float Vector2Dot(Vector2& v1, Vector2& v2);

float Vector2Magnitude(Vector2& vec);

Vector2 Vector2Normalize(Vector2& vec);

float Vector2Distance(Vector2& v1, Vector2& v2);

float Vector2DistanceSquared(Vector2& v1, Vector2& v2);

float Vector2MagnitudeSquared(Vector2& vec);

void Vector2Max(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2Min(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2Clamp(Vector2& vecToClamp, Vector2& min, Vector2& max, Vector2& out);

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

std::string Vector2ToString(Vector2 vec);

Vector2 FromVector3(Vector3& vec);
