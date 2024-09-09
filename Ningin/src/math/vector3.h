#pragma once

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
    Vector3(Vector2 &vec);
};
