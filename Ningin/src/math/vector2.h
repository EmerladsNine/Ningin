#pragma once

#include <format>

using namespace std;

class Vector3; // Forward declaration
class Vector2;


#pragma region Vector2Functions

void Vector2Abs(Vector2& vec, Vector2& out);

void Vector2Inverse(Vector2& vec, Vector2& out);

void Vector2SquareRoot(Vector2& vec, Vector2& out);

float Vector2Dot(Vector2& v1, Vector2& v2);

float Vector2Magnitude(Vector2& vec);

void Vector2Normalize(Vector2& vec, Vector2& out);

float Vector2Distance(Vector2& v1, Vector2& v2);

float Vector2DistanceSquared(Vector2& v1, Vector2& v2);

float Vector2MagnitudeSquared(Vector2& vec);

void Vector2Max(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2Min(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2Clamp(Vector2& vecToClamp, Vector2& min, Vector2& max, Vector2& out);

void Vector2Add(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2Negate(Vector2& vec, Vector2& out);

void Vector2Subtract(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2MultiplyByFloat(Vector2& vec, float a, Vector2& out);

void Vector2Multiply(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2Divide(Vector2& v1, Vector2& v2, Vector2& out);

void Vector2DivideByFloat(Vector2& vec, float a, Vector2& out);

bool Vector2Equals(Vector2& v1, Vector2& v2);

bool Vector2NotEqual(Vector2& v1, Vector2& v2);

bool Vector2L(Vector2& v1, Vector2& v2);

bool Vector2LE(Vector2& v1, Vector2& v2);

bool Vector2G(Vector2& v1, Vector2& v2);

bool Vector2GE(Vector2& v1, Vector2& v2);

void Vector2ToString(Vector2& vec, string& out);

void Vector2FromVector3(Vector3& vec, Vector2& out);

#pragma endregion

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

		void operator*=(const float value)
		{
			Vector2 out;
			Vector2MultiplyByFloat(const_cast<Vector2&>(*this), value, out);
			x = out.x;
			y = out.y;
		}

		Vector2 operator*(const float value)
		{
			Vector2 out;
			Vector2MultiplyByFloat(const_cast<Vector2&>(*this), value, out);
			return out;
		}

		float operator*(const Vector2 value)
		{
			return Vector2Dot(const_cast<Vector2&>(*this), const_cast<Vector2&>(value));
		}

		void operator+=(const Vector2 value)
		{
			Vector2 out;
			Vector2Add(const_cast<Vector2&>(*this), const_cast<Vector2&>(value), out);
			x = out.x;
			y = out.y;
		}

		Vector2 operator+(const Vector2 value)
		{
			Vector2 out;
			Vector2Add(const_cast<Vector2&>(*this), const_cast<Vector2&>(value), out);
			return out;
		}

		void operator-=(const Vector2 value)
		{
			Vector2 out;
			Vector2Subtract(const_cast<Vector2&>(*this), const_cast<Vector2&>(value), out);
			x = out.x;
			y = out.y;
		}

		Vector2 operator-(const Vector2 value)
		{
			Vector2 out;
			Vector2Subtract(const_cast<Vector2&>(*this), const_cast<Vector2&>(value), out);
			return out;
		}
};