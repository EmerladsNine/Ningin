#pragma once

#include <cstdint>
#include <string>

/**
 * A class representing a color with RGBA values.
 */
class Color {
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	/**
	 * Creates a new `Color` instance with the specified RGBA values.
	 *
	 * @param r The red component.
	 * @param g The green component.
	 * @param b The blue component.
	 * @param a The alpha component.
	 * @return A new `Color` instance.
	 */
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	/**
	 * Creates a new `Color` instance where the RGB components have the same value.
	 *
	 * @param rgb The value for the red, green, and blue components.
	 * @return A new `Color` instance.
	 */
	static Color fromRGB(uint8_t rgb);

	/**
	 * Creates a new `Color` instance with the same RGB components as the given color,
	 * but with a different alpha value.
	 *
	 * @param color The base color.
	 * @param a The new alpha value.
	 * @return A new `Color` instance.
	 */
	static Color fromColor(const Color& color, uint8_t a);

	/**
	 * Changes the alpha component of the color.
	 *
	 * @param a The new alpha value.
	 */
	void setAlpha(uint8_t a);

	/**
	 * Converts the color to a string representation.
	 *
	 * @return A string representing the color.
	 */
	std::string toString() const;

	/**
	 * Provides a default `Color` instance (White color).
	 *
	 * @return A `Color` instance with RGB set to 255 and alpha set to 255.
	 */
	static Color defaultColor();
};
