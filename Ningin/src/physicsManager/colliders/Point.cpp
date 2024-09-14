#include "point.h"

// Define the ZERO constant.
const Point Point::ZERO = Point(0, 0);

void PointFromVector2(Vector2& vec, Point& out)
{
	out = Point(static_cast<int>(vec.x), static_cast<int>(vec.y));
}

void PointFromVector3(Vector3& vec, Point& out)
{
	out = Point(static_cast<int>(vec.x), static_cast<int>(vec.y));
}

void PointToString(Point pt, string& out)
{
	out = format("Point - x: {}, y: {}", pt.x, pt.y);
}
