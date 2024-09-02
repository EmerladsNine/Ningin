#include "dimensions2.h"

/**
 * Creates a new `Dimensions2` instance with the specified width and height.
 */
Dimensions2::Dimensions2(int width, int height) : width(width), height(height) {}

/**
 * Creates a default `Dimensions2` instance with width and height set to default values.
 */
Dimensions2::Dimensions2() : width(200), height(200) {}

/**
 * Deconstructs the `Dimensions2` into a tuple of width and height.
 */
std::tuple<int, int> Dimensions2::deconstruct() const {
    return std::make_tuple(width, height);
}

/**
 * Converts the `Dimensions2` to a string representation.
 */
std::string Dimensions2::toString() const {
    return "Dimensions2 - width: " + std::to_string(width) +
        ", height: " + std::to_string(height);
}

/**
 * Formats the `Dimensions2` instance for debugging.
 */
std::ostream& operator<<(std::ostream& os, const Dimensions2& dims) {
    os << "Dimensions2 - width: " << dims.width
        << ", height: " << dims.height;
    return os;
}
