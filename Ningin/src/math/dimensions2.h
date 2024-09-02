#pragma once

#include <string>
#include <tuple>
#include <iostream>

/**
 * This class represents a two-dimensional size (width and height).
 */
class Dimensions2 {
public:
    int width;
    int height;

    /**
     * Creates a new `Dimensions2` instance with the specified width and height.
     *
     * @param width The width of the dimension.
     * @param height The height of the dimension.
     */
    Dimensions2(int width, int height);

    /**
     * Creates a default `Dimensions2` instance with width and height set to default values.
     */
    Dimensions2();

    /**
     * Deconstructs the `Dimensions2` into a tuple of width and height.
     *
     * @return A tuple containing the width and height.
     */
    std::tuple<int, int> deconstruct() const;

    /**
     * Converts the `Dimensions2` to a string representation.
     *
     * @return A string representing the `Dimensions2` instance.
     */
    std::string toString() const;

    /**
     * Formats the `Dimensions2` instance for debugging.
     *
     * @param os The stream to write the output to.
     * @param dims The `Dimensions2` instance to format.
     * @return The output stream with the formatted string.
     */
    friend std::ostream& operator<<(std::ostream& os, const Dimensions2& dims);
};
