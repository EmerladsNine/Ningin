#include "dimensions3.h"

/**
 * Creates a new `Dimensions3` instance with the specified width, height, and depth.
 */
Dimensions3::Dimensions3(int width, int height, int depth) : width(width), height(height), depth(depth)
{
}

/**
 * Creates a default `Dimensions3` instance with default values (200, 200, 200).
 */
Dimensions3::Dimensions3() : width(200), height(200), depth(200)
{
}

/**
 * Deconstructs the `Dimensions3` into a tuple of width, height, and depth.
 */
std::tuple<int, int, int> Dimensions3::deconstruct() const
{
    return std::make_tuple(width, height, depth);
}

/**
 * Converts the `Dimensions3` instance to a string representation.
 */
std::string Dimensions3::toString() const
{
    return "Dimensions3 - width: " + std::to_string(width) + ", height: " + std::to_string(height) +
           ", depth: " + std::to_string(depth);
}

/**
 * Formats the `Dimensions3` instance for debugging.
 */
std::ostream &operator<<(std::ostream &os, const Dimensions3 &dims)
{
    os << "Dimensions3 - width: " << dims.width << ", height: " << dims.height << ", depth: " << dims.depth;
    return os;
}
