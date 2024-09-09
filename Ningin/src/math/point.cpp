#include "point.h"

using namespace std;

// Define the ZERO constant.
const Point Point::ZERO = Point(0, 0);

Point::Point(int x, int y) : x(x), y(y)
{
}

Point::Point() : x(0), y(0)
{
}

pair<int, int> Point::deconstruct()
{
	return { x, y };
}

void Point::set(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point Point_fromVector2(Vector2& vec)
{
	return Point(static_cast<int>(vec.x), static_cast<int>(vec.y));
}

Point Point_fromVector3(Vector3& vec)
{
	return Point(static_cast<int>(vec.x), static_cast<int>(vec.y));
}

string Point_toString(Point pt)
{
	return format("Point - x: {}, y: {}", pt.x, pt.y);
}