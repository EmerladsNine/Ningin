#include "dimensions2.h"

Dimensions2::Dimensions2(unsigned int width, unsigned int height) : width(width), height(height) {}

Dimensions2::Dimensions2() : width(200), height(200) {}

pair<unsigned int, unsigned int> Dimensions2::Deconstruct()
{
	return { width, height };
}

bool Dimensions2::Equal(Dimensions2 dim)
{
	return width == dim.width && height == dim.height;
}

void Dimensions2ToString(Dimensions2& dimensions, string& out)
{
	out = format("Dimensions2 - width: {}, height: {}", dimensions.width, dimensions.height);
}
