#pragma once

#include "../../math/Vector2.h"
#include "../../math/Vector3.h"
#include <format>

class Point
{
	public:
		int x;
		int y;

		static const Point ZERO;

		Point(int x, int y) : x(x), y(y) {}

		Point() : x(0), y(0) {}
};

Point PointFromVector2(Vector2& vec);
Point PointFromVector3(Vector3& vec);
std::string PointToString(Point pt);
