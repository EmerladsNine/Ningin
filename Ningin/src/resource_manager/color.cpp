#include "color.h"
#include <sstream>
#include <iomanip>

/**
 * Creates a new `Color` instance with the specified RGBA values.
 */
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: r(r), g(g), b(b), a(a) {}

/**
 * Creates a new `Color` instance where the RGB components have the same value.
 */
Color Color::fromRGB(uint8_t rgb) {
	return Color(rgb, rgb, rgb, 255);
}

/**
 * Creates a new `Color` instance with the same RGB components as the given color,
 * but with a different alpha value.
 */
Color Color::fromColor(const Color& color, uint8_t a) {
	return Color(color.r, color.g, color.b, a);
}

/**
 * Changes the alpha component of the color.
 */
void Color::setAlpha(uint8_t a) {
	this->a = a;
}

/**
 * Converts the color to a string representation.
 */
std::string Color::toString() const {
	std::stringstream ss;
	ss << "Color - R: " << static_cast<int>(r)
		<< ", G: " << static_cast<int>(g)
		<< ", B: " << static_cast<int>(b)
		<< ", A: " << static_cast<int>(a);
	return ss.str();
}

/**
 * Provides a default `Color` instance (White color).
 */
Color Color::defaultColor() {
	return Color(255, 255, 255, 255);
}