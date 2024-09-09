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
