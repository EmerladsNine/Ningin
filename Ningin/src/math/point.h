#pragma once

#include "vector2.h"
#include "vector3.h"
#include <format>

class Point
{
  public:
    int x;
    int y;

    static const Point ZERO;

    Point(int x, int y);

    Point();

    std::pair<int, int> deconstruct();

    void set(int x, int y);
};
