#pragma once

#include <string>
#include <iostream>
#include "tuple"

/**
 * A class representing a three-dimensional size (width, height, and depth).
 */
class Dimensions3 {
public:
	int width;
	int height;
	int depth;

	/**
	 * Creates a new `Dimensions3` instance with the specified width, height, and depth.
	 *
	 * @param width The width of the dimension.
	 * @param height The height of the dimension.
	 * @param depth The depth of the dimension.
	 */
	Dimensions3(int width, int height, int depth);

	/**
	 * Creates a default `Dimensions3` instance with default values (200, 200, 200).
	 */
	Dimensions3();

	/**
	 * Deconstructs the `Dimensions3` into a tuple of width, height, and depth.
	 *
	 * @return A tuple containing the width, height, and depth.
	 */
	std::tuple<int, int, int> deconstruct() const;

	/**
	 * Converts the `Dimensions3` instance to a string representation.
	 *
	 * @return A string representing the `Dimensions3` instance.
	 */
	std::string toString() const;

	/**
	 * Formats the `Dimensions3` instance for debugging.
	 *
	 * @param os The stream to write the output to.
	 * @param dims The `Dimensions3` instance to format.
	 * @return The output stream with the formatted string.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Dimensions3& dims);
};
