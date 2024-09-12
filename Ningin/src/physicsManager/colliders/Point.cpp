#include "point.h"

using namespace std;

// Define the ZERO constant.
const Point Point::ZERO = Point(0, 0);

Point PointFromVector2(Vector2& vec)
{
	return Point(static_cast<int>(vec.x), static_cast<int>(vec.y));
}

Point PointFromVector3(Vector3& vec)
{
	return Point(static_cast<int>(vec.x), static_cast<int>(vec.y));
}

string PointToString(Point pt)
{
	return format("Point - x: {}, y: {}", pt.x, pt.y);
}