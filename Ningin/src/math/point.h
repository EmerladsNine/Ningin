#pragma once

#include "vector2.h"
#include "vector3.h"
#include <iostream>
#include <string>

/**
 * This structure is used to define a point in a 2D space with x and y coordinates.
 */
class Point
{
  public:
    int x;
    int y;

    /**
     * A constant representing a Point at the origin (0, 0).
     */
    static const Point ZERO;

    /**
     * Creates a new point with the given x and y coordinates.
     *
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     */
    Point(int x, int y);

    /**
     * Creates a default `Point` instance with components set to zero.
     */
    Point();

    /**
     * Deconstructs the `Point` into a pair containing the x and y coordinates.
     *
     * @return A pair representing the x and y coordinates of the point.
     */
    std::pair<int, int> deconstruct() const;

    /**
     * Sets the x and y coordinates of the point.
     *
     * @param x The new x-coordinate.
     * @param y The new y-coordinate.
     */
    void set(int x, int y);

    /**
     * Converts a `Vector2` to a `Point`.
     *
     * @param vec The `Vector2` to convert.
     * @return A `Point` created from the `Vector2`.
     */
    static Point fromVector2(const Vector2 &vec);

    /**
     * Converts a `Vector3` to a `Point`.
     *
     * @param vec The `Vector3` to convert.
     * @return A `Point` created from the `Vector3`.
     */
    static Point fromVector3(const Vector3 &vec);

    /**
     * Converts the point to a string representation.
     *
     * @return A string representing the point.
     */
    std::string toString() const;

    /**
     * Formats the point for debugging.
     *
     * @param os The stream to write the output to.
     * @param point The `Point` instance to format.
     * @return The output stream with the formatted string.
     */
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};
