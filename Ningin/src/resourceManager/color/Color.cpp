#include "Color.h"
#include "../../ningin.h"

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
	: r(static_cast<unsigned int>(RangeBoundValue(colorRange, static_cast<float>(r)))),
	g(static_cast<unsigned int>(RangeBoundValue(colorRange, static_cast<float>(g)))),
	b(static_cast<unsigned int>(RangeBoundValue(colorRange, static_cast<float>(b)))),
	a(static_cast<unsigned int>(RangeBoundValue(colorRange, static_cast<float>(a)))) {}

Color::Color() : r(255), g(255), b(255), a(255) {}

bool Color::operator==(Color& other)
{
	return r == other.r && b == other.b && g == other.g && a == other.a;
}

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
	color.a = static_cast<unsigned int>(RangeBoundValue(colorRange, static_cast<float>(a)));
}

void ColorToString(Color& color, string& out)
{
	out = format("Color - r: {}, g: {}, b: {}, a: {}", color.r, color.g, color.b, color.a);
}
