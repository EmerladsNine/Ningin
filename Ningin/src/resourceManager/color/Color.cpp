#include "Color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

Color::Color() : r(255), g(255), b(255), a(255) {}

void ColorFromRGB(uint8_t rgb, Color& out)
{
	out = Color(rgb, rgb, rgb, 255);
}

void ColorFromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a, Color& out)
{
	out = Color(r, g, b, a);
}

void ColorFromColor(Color& color, uint8_t a, Color& out)
{
	out = Color(color.r, color.g, color.b, a);
}

void ColorSetAlpha(Color& color, uint8_t a)
{
	color.a = a;
}

void ColorToString(Color& color, string& out)
{
	out = format("Color - r: {}, g: {}, b: {}, a: {}", color.r, color.g, color.b, color.a);
}
