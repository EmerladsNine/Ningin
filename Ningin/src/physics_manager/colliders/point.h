#pragma once

#include "../../math/vector2.h"
#include "../../math/vector3.h"
#include <format>

class Point
{
  public:
    int x;
    int y;

    static const Point ZERO;

    Point(int x, int y): x(x), y(y) {}

    Point(): x(0), y(0) {}
};

Point Point_fromVector2(Vector2& vec);
Point Point_fromVector3(Vector3& vec);
std::string Point_toString(Point pt);
