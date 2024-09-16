#include "color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

Color Color::FromRGB(uint8_t rgb)
{
	return Color(rgb, rgb, rgb, 255);
}

Color Color::FromColor(Color& color, uint8_t a)
{
	return Color(color.r, color.g, color.b, a);
}

void Color::SetAlpha(uint8_t a)
{
	this->a = a;
}

string Color::ToString()
{
	return format("Color - r: {}, g: {}, b: {}, a: {}", static_cast<int>(r), static_cast<int>(g),
		static_cast<int>(b), static_cast<int>(a));
}

Color Color::DefaultColor()
{
	return Color(255, 255, 255, 255);
}
