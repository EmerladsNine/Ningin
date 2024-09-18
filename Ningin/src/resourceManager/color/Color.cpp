#include "Color.h"
#include "../../ningin.h"

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
	: r(RangeBoundValue(colorRange, r)), g(RangeBoundValue(colorRange, g)), b(RangeBoundValue(colorRange, b)),
	a(RangeBoundValue(colorRange, a)) {}

Color::Color() : r(255), g(255), b(255), a(255) {}

void ColorFromRGB(unsigned int rgb, Color& out)
{
	out = Color(rgb, rgb, rgb, 255);
}

void ColorFromRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a, Color& out)
{
	out = Color(r, g, b, a);
}

void ColorFromColor(Color& color, unsigned int a, Color& out)
{
	out = Color(color.r, color.g, color.b, a);
}

void ColorSetAlpha(Color& color, unsigned int a)
{
	color.a = RangeBoundValue(colorRange, a);
}

void ColorToString(Color& color, string& out)
{
	out = format("Color - r: {}, g: {}, b: {}, a: {}", color.r, color.g, color.b, color.a);
}
