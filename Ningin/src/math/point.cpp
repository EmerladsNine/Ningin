#include "point.h"

// Define the ZERO constant.
const Point Point::ZERO = Point(0, 0);

/**
 * Creates a new point with the given x and y coordinates.
 */
Point::Point(int x, int y) : x(x), y(y)
{
}

/**
 * Creates a default `Point` instance with components set to zero.
 */
Point::Point() : x(0), y(0)
{
}

/**
 * Deconstructs the `Point` into a pair containing the x and y coordinates.
 */
std::pair<int, int> Point::deconstruct() const
{
    return {x, y};
}

/**
 * Sets the x and y coordinates of the point.
 */
void Point::set(int x, int y)
{
    this->x = x;
    this->y = y;
}

/**
 * Converts a `Vector2` to a `Point`.
 */
Point Point::fromVector2(const Vector2 &vec)
{
    return Point(static_cast<int>(vec.x), static_cast<int>(vec.y));
}

/**
 * Converts a `Vector3` to a `Point`.
 */
Point Point::fromVector3(const Vector3 &vec)
{
    return Point(static_cast<int>(vec.x), static_cast<int>(vec.y));
}

/**
 * Converts the point to a string representation.
 */
std::string Point::toString() const
{
    return "Point - x: " + std::to_string(x) + ", y: " + std::to_string(y);
}

/**
 * Formats the point for debugging.
 */
std::ostream &operator<<(std::ostream &os, const Point &point)
{
    os << "Point - x: " << point.x << ", y: " << point.y;
    return os;
}
