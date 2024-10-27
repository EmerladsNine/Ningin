#pragma once

#include <string>

using namespace std;

class Vector2;
class Vector3;

#pragma region Vector3Functions

void Vector3Abs(Vector3& vec, Vector3& out);

void Vector3Inverse(Vector3& vec, Vector3& out);

void Vector3SquareRoot(Vector3& vec, Vector3& out);

float Vector3Magnitude(Vector3& vec);

void Vector3Normalize(Vector3& vec, Vector3& out);

float Vector3Dot(Vector3& v1, Vector3& v2);

float Vector3Distance(Vector3& v1, Vector3& v2);

float Vector3DistanceSquared(Vector3& v1, Vector3& v2);

float Vector3MagnitudeSquared(Vector3& vec);

void Vector3Max(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3Min(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3Clamp(Vector3& vecToClamp, Vector3& min, Vector3& max, Vector3& out);

void Vector3Add(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3Negate(Vector3& vec, Vector3& out);

void Vector3Subtract(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3MultiplyByFloat(Vector3& vec, float a, Vector3& out);

void Vector3Multiply(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3Divide(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3DivideByFloat(Vector3& vec, float a, Vector3& out);

bool Vector3Equals(Vector3& v1, Vector3& v2);

bool Vector3NotEqual(Vector3& v1, Vector3& v2);

bool Vector3L(Vector3& v1, Vector3& v2);

bool Vector3LE(Vector3& v1, Vector3& v2);

bool Vector3G(Vector3& v1, Vector3& v2);

bool Vector3GE(Vector3& v1, Vector3& v2);

void Vector3Cross(Vector3& v1, Vector3& v2, Vector3& out);

void Vector3ToString(Vector3& vec, string& out);

void Vector3FromVector2(Vector2& vec, Vector3& out);

#pragma endregion

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

		void operator*=(const float value)
		{
			Vector3 out;
			Vector3MultiplyByFloat(const_cast<Vector3&>(*this), value, out);
			x = out.x;
			y = out.y;
			z = out.z;
		}

		Vector3 operator*(const float value)
		{
			Vector3 out;
			Vector3MultiplyByFloat(const_cast<Vector3&>(*this), value, out);
			return out;
		}

		float operator*(const Vector3 value)
		{
			return Vector3Dot(const_cast<Vector3&>(*this), const_cast<Vector3&>(value));
		}


		void operator+=(const Vector3 value)
		{
			Vector3 out;
			Vector3Add(const_cast<Vector3&>(*this), const_cast<Vector3&>(value), out);
			x = out.x;
			y = out.y;
			z = out.z;
		}

		Vector3 operator+(const Vector3 value)
		{
			Vector3 out;
			Vector3Add(const_cast<Vector3&>(*this), const_cast<Vector3&>(value), out);
			return out;
		}

		void operator-=(const Vector3 value)
		{
			Vector3 out;
			Vector3Subtract(const_cast<Vector3&>(*this), const_cast<Vector3&>(value), out);
			x = out.x;
			y = out.y;
			z = out.z;
		}

		Vector3 operator-(const Vector3 value)
		{
			Vector3 out;
			Vector3Subtract(const_cast<Vector3&>(*this), const_cast<Vector3&>(value), out);
			return out;
		}

		Vector3 operator%(const Vector3 value)
		{
			Vector3 out;
			Vector3Cross(const_cast<Vector3&>(*this), const_cast<Vector3&>(value), out);
			return out;
		}

		void operator%=(const Vector3 value)
		{
			Vector3 out;
			Vector3Cross(const_cast<Vector3&>(*this), const_cast<Vector3&>(value), out);
			x = out.x;
			y = out.y;
			z = out.z;
		}
};