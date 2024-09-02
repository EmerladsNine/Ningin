#pragma once

#include <cmath>
#include <stdexcept>

class math {
public:
	/**
	 * Clamps a given value within a specified range.
	 *
	 * @param val_to_clamp The value that needs to be clamped.
	 * @param min The minimum value to which `val_to_clamp` shouldn't subceed.
	 * @param max The maximum value to which `val_to_clamp` shouldn't exceed.
	 * @return The clamped value, ensuring it is within the specified range.
	 */
	static float clamp(float val_to_clamp, float min, float max);

	/**
	 * Converts degrees to radians.
	 *
	 * @param deg The angle in degrees to be converted.
	 * @return The angle converted to radians.
	 */
	static float degrees_to_radians(float deg);

	/**
	 * Computes the nth root (radical) of a given number.
	 *
	 * @param number The number for which the nth root is to be computed.
	 * @param n The degree of the root.
	 * @return The nth root of `number`.
	 * @throws std::invalid_argument if `number` is negative and `n` is even.
	 */
	static double radical(double number, int n);

	static const double PI = 3.14159265358979323846;
	static const double EPSILON = 1e-6;
};
